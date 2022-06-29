from collections import namedtuple
import csv
import os
import subprocess
import re
import sys
# import random #for testing only
# import time #for testing only
from typing import Iterable

#args = sys.argv #filename csv_path

CommonFieldTree = namedtuple('CommonFieldTree', 'UsedPieceIndex SolvePercent childNodes')
CommonFieldTree.__doc__ = '''\
UsedPieceIndex: int - index of piece (order set by myself) following tree of used pieces
SolvePercent: float - percentage of all solves that cover the remaining queues
childNodes: set | dict - dict of CommonFieldTree elements, or set of SetupIndexes (only applicable it is a leaf node)'''

TetrominoDict = {
    "I": set(range(0,37+1)),
    "L": set(range(38,121+1)),
    "J": set(range(122,205+1)),
    "O": set(range(206,232+1)),
    "S": set(range(233,274+1)),
    "T": set(range(275,358+1)),
    "Z": set(range(359,400+1)),
}

FullBag = {"T", "I", "O", "J", "L", "S", "Z"}
SFinderDir = os.path.dirname(r"****\v1.21\\")
FileDir = os.path.dirname(os.path.realpath('__file__'))

def ReturnTetromino(Index: int) -> str:
    for Tetromino in TetrominoDict:
        if Index in TetrominoDict[Tetromino]: 
            return Tetromino
    raise ValueError('Index not in TetrominoDict.')

def PieceIndexesToTetromino(Indexes: set[int]) -> set:
    return {ReturnTetromino(index) for index in Indexes}

def ReadCSV(Filename: str) -> list[list[str]]:
    print(f"reading: {Filename}")
    inputCSV = [row for row in csv.reader(open(Filename, 'r'))]
    print('finished')
    return inputCSV

def AddToDict(Dict: dict, Key, Item: set): #TODO: I used to do this to get around initializing dicts badly by reflecting the same element, but now that I understand the problem, I want to update the function so that it can be simpler
    if Key in Dict:
        newVal = Dict[Key].copy()
        newVal.update(Item)
        Dict.update({Key : newVal})
    else:
        Dict[Key] = Item

def DictToTuple(Dict: dict) -> tuple:
    return tuple([tuple([key, frozenset(value)]) for key, value in zip(Dict.keys(), Dict.values())])

def PrintTree(Tree: CommonFieldTree, Indent: int):
    tab = "\t"
    print(f'{tab*Indent}{Tree.UsedPieceIndex}\t{Tree.SolvePercent*100:.2f}%')
    if isinstance(Tree.childNodes, frozenset):
        # for fumenIndex in Tree.childNodes:
        #     print(f'{tab*(Indent+1)}{fumenIndex}: {FumenList[fumenIndex]}')
        return
    for node in Tree.childNodes:
        print(f'{tab*(Indent+1)}{node[0]}')
        for childnode in node[1]:
            PrintTree(childnode, Indent+2)

def CoverCSVToDict(CoverCSV: list[list[str]], FieldIndexes: Iterable) -> dict:
    sequences = [coverRow[0] for coverRow in CoverCSV[1:]]
    cover = [coverRow[1:] for coverRow in CoverCSV[1:]]

    CoverDictByQueue = dict()
    for queueIndex in range(len(cover)):
        CoverDictByQueue[sequences[queueIndex]] = {setupIndex for setupIndex, success in zip(FieldIndexes, cover[queueIndex]) if success == "O"}
    return CoverDictByQueue

class Validator:
    def __ReturnCommandOutput(self, Command: list, LogCommand: bool = True) -> str:
        if LogCommand: print(" ".join(Command))
        Pipe = subprocess.Popen(Command, stdout=subprocess.PIPE)
        output, error = Pipe.communicate()
        Pipe.kill()
        if (error != None): raise error
        return output.decode("utf-8")[:-1] #chop off \n

    def __ReturnSfinderOutput(self, SFinderCommand: str) -> str:
        SFinderPath = os.path.join(SFinderDir, "sfinder.jar")
        return self.__ReturnCommandOutput(["java", "-jar", SFinderPath, *SFinderCommand.split(" ")], False)

    def __IndexesToFumen(self, Tetromino: str, Indexes: set[int]) -> str:
        return self.__ReturnCommandOutput(f"node indexes-to-fumen.js {Tetromino} {' '.join(map(str, Indexes))}".split(" "), False)

    # SfinderPercent([0, 274, 381, 171], ["[TOL]!,*p4"])
    def SfinderPercent(self, UsedPieceIndexes: set[int], CoverSequences: set[str]) -> float:
        Field = self.__IndexesToFumen("X", UsedPieceIndexes)
        PatternPath = os.path.join(FileDir, r"temp\pattern_temp.txt")
        print("\n".join(CoverSequences), file=open(PatternPath, "w"))

        if(" " in PatternPath): raise NotImplementedError("Currently the file paths cannot contain whitespace.")
        SfinderOutput = self.__ReturnSfinderOutput(f"percent -H use -t {Field} -P 1 -pp {PatternPath} -c 4 -d softdrop -th -1 -td 0 -fc 0")
        RegexMatch = re.search("success = ([\d.]+)%", SfinderOutput)
        if not isinstance(RegexMatch, re.Match): raise ValueError("No match was found.")
        return float(RegexMatch.group(1))/100

class BuildChecker:
    BuildableRecord = set()

    def __init__(self, BuildableRecord: set = set()):
        self.BuildableRecord = BuildableRecord

    def __ReturnCommandOutput(self, Command: list, LogCommand: bool = True) -> str:
        if LogCommand: print(" ".join(Command))
        Pipe = subprocess.Popen(Command, stdout=subprocess.PIPE)
        output, error = Pipe.communicate()
        Pipe.kill()
        if (error != None): raise error
        return output.decode("utf-8")[:-1] #chop off \n
    
    def AddRecord(self, extRecord: set[frozenset]):
        self.BuildableRecord.update(extRecord)
    
    def PossibleToBuildv3(self, Indexes: set[int]) -> bool: #no repeats or supersets allowed
        if tuple(sorted(Indexes)) in self.BuildableRecord:
            return False
        commandOutput = self.__ReturnCommandOutput(f"node check-index-buildable.js {' '.join(map(str, Indexes))}".split(" "), False)
        if (commandOutput == "true"):
            output = True
            self.BuildableRecord.update({tuple(sorted(Indexes))}) #only buildable options are checked for percentage
        else:
            output = False
        return output

_numSetupPieces = 4
_numEqualPieces = 0
_increasedSeePiecesPerPlacement = 0 # usually set to 1, as you see 1 new piece from the next bag for each piece you place.
#remaining pieces are "blind", you have to conform to the constraints
_recurseDepth = 4 #the number of pieces placed

class SetupPoolWithoutCover:
    # does not narrow down search with the piece indexes seen in the cover, rather calls sfinder directly.
    # as a result, FieldIndex and CoverDict are absent
    TreeSucceedPercentage = 0.1 #include current tree if it contains at least this percentage of maximum child nodes
    SolveThresholdPercentage = 0.7595 #the percentage of queues that a node should at least cover
    ValidatorObj = Validator()


    def __init__(self, Layer: int, UsedPieceIndexes: set, prevBuildCheckerObj: BuildChecker): 
        self.Layer = Layer
        self.UsedPieceIndexes = UsedPieceIndexes
        # self.ValidatorObj = ValidatorObj
        self.prevBuildCheckerObj = prevBuildCheckerObj

    def __CreateNewSeqDict(self, Sequences: list, SamePieces: int) -> dict:
        NewSeqDict = {}
        for Queue in Sequences:
            AddToDict(NewSeqDict, Queue[0:SamePieces], {Queue})
        return NewSeqDict
    
    def __CalculateSolvePercentage(self, UsedPieceIndexes: set[int], CoverSequences: set[int]) -> float:
        return self.ValidatorObj.SfinderPercent(UsedPieceIndexes, CoverSequences)
    
    def __ReturnTree(self, CurrentPieceIndex: set, CoverSequences: set[str], CurrentSolvePercent: float) -> CommonFieldTree:
        if (self.Layer == _recurseDepth): #last layer, return the inputted FieldIndexes that are solvable
            return CommonFieldTree(CurrentPieceIndex, CurrentSolvePercent, frozenset())
        
        AllUsedPieceIndexes = set()
        if (self.Layer >= 1): AllUsedPieceIndexes = {CurrentPieceIndex} | self.UsedPieceIndexes
        
        NumSamePieces = _numSetupPieces + _numEqualPieces + (_increasedSeePiecesPerPlacement - 1) * self.Layer
        #remove the piece used in coversequence
        newCoverSequences = CoverSequences
        if (self.Layer >= 1): newCoverSequences = [sequence.replace(ReturnTetromino(CurrentPieceIndex), "", 1) for sequence in newCoverSequences]
        newSeqDict = self.__CreateNewSeqDict(newCoverSequences, NumSamePieces) #iterate over newSeqDict.values() to get the next CoverSequences
                        
        # for each tetromino seen in sequence, collect (pool.ReturnTree with all setups containing the piece, per candidate piece, per subset of sequence)
        # ReachablePieces = list(newCoverSequences)[0][:2]
        ReachablePieces = list(newSeqDict.keys())[0][:2] #only applies when there is one key in SeqDict
        possibleNextPieceIndexes = set()
        [possibleNextPieceIndexes.update(TetrominoDict[possibleNextPiece]) for possibleNextPiece in ReachablePieces]

        # get union of all remaining pieceIndexes & filter pieces with same tetromino as piece
        possibleNextPieceIndexes = {x for x in possibleNextPieceIndexes if self.prevBuildCheckerObj.PossibleToBuildv3(AllUsedPieceIndexes | {x})}
        candidatePieceIndexes = possibleNextPieceIndexes - AllUsedPieceIndexes
        
        newPool = SetupPoolWithoutCover(self.Layer+1, AllUsedPieceIndexes, self.prevBuildCheckerObj)
        if self.Layer == 0:
            Output = set()
            candidatePieceIndexes = candidatePieceIndexes
            print(f"candidates({self.Layer}): {AllUsedPieceIndexes} + {candidatePieceIndexes}")
            for candidatePieceIndex in candidatePieceIndexes:
                # print('first piece:', candidatePieceIndex)
                result = newPool.__ReturnTree(candidatePieceIndex, CoverSequences, CurrentSolvePercent)
                if result != set():
                    Output.update({result})
            return Output
        else:

            # eliminate unbuildable fields from candidates
            # candidatePieceIndexes = {candidateIndex for candidateIndex in candidatePieceIndexes if self.ValidatorObj.PossibleToBuildv2(AllUsedPieceIndexes | {candidateIndex})} #debug

            # only call recursion for sequences with full cover with the picked PieceIndex
            ResultDict = {}
            for i in range(len(newSeqDict.keys())):
                SeqDictKey = list(newSeqDict.keys())[i]
                print(f"candidates({self.Layer}): {AllUsedPieceIndexes} + {candidatePieceIndexes}")
                for candidatePieceIndex in candidatePieceIndexes: 
                    # filter out fields that do not cover the current sequences
                    # print(f"trying: {AllUsedPieceIndexes | {candidatePieceIndex}}")
                    CandidateCoverSequences = [sequence.replace(ReturnTetromino(candidatePieceIndex), "", 1) for sequence in newCoverSequences]
                    nextSolvePercent =  self.__CalculateSolvePercentage(AllUsedPieceIndexes | {candidatePieceIndex}, CandidateCoverSequences)
                    # print(f"{nextSolvePercent*100:.2f}")
                    if nextSolvePercent < self.SolveThresholdPercentage: continue

                    print(f"progress: {AllUsedPieceIndexes | {candidatePieceIndex}}, {nextSolvePercent*100:.2f}")
                    result = newPool.__ReturnTree(candidatePieceIndex, newSeqDict[SeqDictKey], nextSolvePercent)
                    if result != set():
                        AddToDict(ResultDict, SeqDictKey[_numSetupPieces-self.Layer:], {result}) #record to dict by next bag pieces
                # if there isn't at least one valid cover for the current set of sequences, it fails to completely cover, so return empty set
                # if (SeqDictKey[_numSetupPieces-self.Layer:] not in ResultDict): 
                    # return set()
                failBranches = (i+1) - len(ResultDict)
                if failBranches / len(newSeqDict) > (1-self.TreeSucceedPercentage):
                    return set()
            
            # Termination: return all fields that cover the final queue
            # print('return', DictToTuple(ResultDict))
            return CommonFieldTree(CurrentPieceIndex, CurrentSolvePercent, DictToTuple(ResultDict))
    
    def newStart(self) -> list: 
        newSeqDict = self.__CreateNewSeqDict(Sequences, _numSetupPieces + _numEqualPieces)
        newPool = SetupPoolWithoutCover(self.Layer+1, set(), self.prevBuildCheckerObj)
        Output = []

        for sequenceKey in newSeqDict.keys():
            print(f'trying: {sequenceKey}')
            
            # assume 0p is always possible
            # nextSolvePercent = self.__CalculateSolvePercentage(set(), newSeqDict[sequenceKey])
            # if nextSolvePercent < self.SolveThresholdPercentage: continue

            Output.append(newPool.__ReturnTree(set(), newSeqDict[sequenceKey], 1.0))
        return Output

class TreeMerger:
    def __MergeTuples(self, TupleA: tuple, TupleB: tuple) -> tuple:
        #sanity check
        if (TupleA[0] != TupleB[0]): raise ValueError("Tuples provided should not be combined.")
        #combine frozenset of trees, merge trees with same UsedPieceIndex
        return (TupleA[0], self.ReturnMergedTrees(TupleA[1] | TupleB[1]))
        
    def __RecurseMergeTree(self, TreeA: CommonFieldTree, TreeB: CommonFieldTree) -> CommonFieldTree:
        #if the pieceIndexes are the same, that means each sub-section of sequences can be merged.
        #if the pieceIndex of a tree is the same inside the sequence sub-section, recurse.
        #if leaves are merged, combine the set of solutions.

        #sanity check
        if (TreeA.UsedPieceIndex != TreeB.UsedPieceIndex): raise ValueError("Trees provided should not be combined, they do not have the same pieceIndex.")
        newUsedPieceIndex = TreeA.UsedPieceIndex

        if isinstance(TreeA.childNodes, tuple):
            MaximumBranches = round(len(TreeA.childNodes) / TreeA.SolvePercent)
            AllTuples = TreeA.childNodes + TreeB.childNodes
            CombinedTuples = []
            SequenceRecord = []
            for Tuple in AllTuples:
                Tuple = (Tuple[0], Tuple[1])
                if (Tuple[0] in SequenceRecord):
                    index = SequenceRecord.index(Tuple[0])
                    CombinedTuples[index] = self.__MergeTuples(CombinedTuples[index], Tuple)
                else:
                    SequenceRecord.append((Tuple[0]))
                    CombinedTuples.append(Tuple)
            return CommonFieldTree(newUsedPieceIndex, len(CombinedTuples) / MaximumBranches, tuple(CombinedTuples))
        elif isinstance(TreeA.childNodes, frozenset):
            if (TreeA.SolvePercent > TreeB.SolvePercent): #just pick the one with higher percent (not applicable to oqb research)
                return TreeA
            else:
                return TreeB
        else: raise TypeError("Unexpected childNode type.")

    def ReturnMergedTrees(self, Trees: list[CommonFieldTree]) -> frozenset:
        CombinedTreesDict = dict()
        for Tree in Trees:
            if (Tree.UsedPieceIndex in CombinedTreesDict):
                CombinedTreesDict[Tree.UsedPieceIndex] = self.__RecurseMergeTree(CombinedTreesDict[Tree.UsedPieceIndex], Tree)
            else:
                CombinedTreesDict[Tree.UsedPieceIndex] = Tree
        return frozenset(CombinedTreesDict.values())

####
# prep
print("Begin prep")

SequenceFile = "sequence.txt"

Sequences = []
[Sequences.extend(x) for x in ReadCSV(os.path.join(FileDir, SequenceFile))]
# BagResiduePieces = set(Sequences[0][:_numSetupPieces]) #what types of pieces are used for the setup pieces

SeqDict = {}
for i in range(len(Sequences)):
    sequence = Sequences[i]
    # SeeableLength = _numSetupPieces + 2 * _numEqualPieces - 1
    SeeableLength = _numSetupPieces + _numEqualPieces + (_recurseDepth - 1) * _increasedSeePiecesPerPlacement
    SeeableLength = _increasedSeePiecesPerPlacement

    SeeableSequence = sequence[0:SeeableLength] # 9 pieces are seen before 3p is placed
    AddToDict(SeqDict, SeeableSequence, {sequence})

OutputFile = f'congruent_output_LS-LJ.txt'

#compute

# ValidatorObj = Validator()
print("Begin searching for congruents")
QueueTrees = SetupPoolWithoutCover(-1, set(), BuildChecker(set())).newStart()
AllTrees = []
for Trees in QueueTrees:
    AllTrees.extend(list(Trees))

#merge

print("Merging trees")
AllTrees = TreeMerger().ReturnMergedTrees(AllTrees)
        
#output

print(f"writing: {OutputFile}")
with open(OutputFile, 'w') as f:
    stdout_original = sys.stdout
    sys.stdout = f
    for tree in AllTrees:
        PrintTree(tree, 0)
    sys.stdout = stdout_original