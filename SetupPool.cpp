#include <iostream>
#include <stdexcept>
#include "./SetupPool.h"
#include "Misc/CommonDataTypes.h"
#include "./Field.h"

map<string, set<string>> SetupPool::CreateNewSeqMap(const set<string>& Sequences, int SamePieces) {
    map<string, set<string>> NewSeqMap = {};
    for (auto Queue : Sequences) {
        AddToSeqMap(NewSeqMap, Queue.substr(0, SamePieces), Queue);
    }
    return NewSeqMap;
}

void SetupPool::AddToSeqMap(map<string, set<string>>& Map, string Key, string Entry) {
    auto MapIter = Map.find(Key);
    if (MapIter != Map.end()) {
        Map[Key].insert(Entry);
    }
    else {
        Map[Key] = { Entry };
    }
}

string SetupPool::PiecesToString(unordered_set<Piece> Pieces) {
    string Content = "";
    for (const auto& piece : Pieces) {
        string newString = std::to_string(piece.AsIndex()) + ", ";
        Content.insert(Content.end(), newString.begin(), newString.end());
    }
    return "{" + Content.substr(0,Content.size()-2) + "}";
}

SetupPool::CommonFieldTree SetupPool::ReturnTree(Piece CurrentPiece, set<string> CoverSequences, double CurrentSolvePercent, string SetupPieceSequence) { //TODO: setup SetupPieceSequence should really be initialized from the SetupPool constructor, but then I would need to use multiple SetupPools at Start() to assign the correct setup sequence to each pool.
    /*set<int> AllUsedPieceIndexes;*/
    unordered_set<Piece> AllUsedPieces = UsedPieces.AsPieces();
    AllUsedPieces.insert(CurrentPiece);

    if (Layer == Config.GetValueInt("--placed-pieces")) {
        std::cout << "New setup found: " << PiecesToString(AllUsedPieces) << "\n";
        set<string> SetupSequences = PercentageRecordObj.ReturnSetupSequences();
        for (const auto & sequence : ValidatorObj.ReturnCoveredQueues(AllUsedPieces, SetupSequences)) {
            PercentageRecordObj.UpdatePercentage(sequence, CurrentSolvePercent);
        };
        
        std::cout << "Current best: " << PercentageRecordObj.BestPercentagesString() << "\n";
        
        //print out the global array of percentage each time a better field is found
        //"current best for each sequence: ..."
        string Fumen = Field(AllUsedPieces).AsFumen(true);
        std::cout << Fumen << "\n";
        return { CurrentPiece, CurrentSolvePercent, {{Fumen, {}}} }; //format abuse, only leaves will have empty vector of trees
    }

    int NumSamePieces = Config.GetValueInt("--visible-pieces") + (Config.GetValueInt("--increased-vision") - 1) * Layer;
    //remove the piece used in coversequence
    set<string> newCoverSequences;
    for (auto sequence : CoverSequences) {
        auto pos = sequence.find(CurrentPiece.AsTetromino());
        if (pos == std::string::npos) throw std::runtime_error("Piece to remove from sequence does not exist.");
        newCoverSequences.insert(sequence.replace(pos, 1, ""));
    }
    map<string, set<string>> newSeqMap = CreateNewSeqMap(newCoverSequences, NumSamePieces); //iterate over newSeqDict.values() to get the next CoverSequences
    // for each tetromino seen in sequence, collect (pool.ReturnTree with all setups containing the piece, per candidate piece, per subset of sequence)

    auto randomIt = newSeqMap.begin();
    std::advance(randomIt, rand() % newSeqMap.size());
    string ReachablePieces = randomIt->first.substr(0, 2);
    unordered_set<Piece> possibleNextPieces;
    for (auto possibleNextPiece : ReachablePieces) {
        set<int> newPieceIndexes = TetrominoDict.at(possibleNextPiece);
        possibleNextPieces.insert(newPieceIndexes.begin(), newPieceIndexes.end());
    }
    for (const auto& usedPiece : AllUsedPieces) {
        possibleNextPieces.erase(usedPiece);
    }

    // get union of all remaining pieces & filter pieces with same tetromino as piece
    unordered_set<Piece> candidatePieces;
    for (auto x : possibleNextPieces) {
        unordered_set<Piece> nextUsedPieces = AllUsedPieces;
        nextUsedPieces.insert(x);
        if (BuildCheckerObj.isBuildable(nextUsedPieces, Layer >= Config.GetValueInt("--visible-pieces") - 3)) { //this should be vis - 3 instead of 1(as first True) for 4?
            candidatePieces.insert(x);
        }
        else {
            //std::cout << SetToString(nextUsedPieces) << " failed.\n";
        }
    }
    

    //manual pruning
    //set<int> r;
    ////if (Layer == 0) {
    ////    r = { 249, 250, 251, 252, 253 };
    ////} if (Layer == 1) {
    ////    r = { 126, 127, 128, 129, 133 };
    ////} if (Layer == 2) {
    ////    r = { 233, 236, 237, 238, 242, 243 };
    ////} if (Layer == 3) {
    ////    r = { 361, 362 };
    ////}
    //for (auto i : r) {
    //    candidatePieces.erase(i);
    //}


    SetupPool newPool(Layer + 1, AllUsedPieces, BuildCheckerObj, ValidatorObj, Config, PercentageRecordObj);
    //eliminate unbuildable fields from candidates

    //only call recursion for sequences with full cover with the picked PieceIndex
    vector<std::pair<string, vector<CommonFieldTree>>> OutputNodes;
    int LoopCount = 0;
    for (const auto& SeqMapEntry : newSeqMap) {
        std::cout << "candidates(" << Layer << "): " << PiecesToString(AllUsedPieces) << " + " << candidatePieces.size() << "\n";
        for (auto candidatePiece : candidatePieces) {
            //filter out fields that do not cover the current sequences
            unordered_set<Piece> nextUsedPieces = AllUsedPieces;
            nextUsedPieces.insert(candidatePiece);

            set<string> CandidateCoverSequences;
            for (auto sequence : newCoverSequences) {
                auto pos = sequence.find(candidatePiece.AsTetromino());
                if (pos == std::string::npos) throw std::runtime_error("Piece to remove from sequence does not exist.");
                CandidateCoverSequences.insert(sequence.replace(pos, 1, ""));
            }

            //std::cout << "trying: " << SetToString(nextUsedPieceIndexes) << "\n";
            
            //shortcut re-checking percentages already confirmed by sfinder
            double currentSolveThresholdPercentage = PercentageRecordObj.GetThreshold();
            bool AboveThreshold = PercentageRecordObj.SetupAboveThreshold(nextUsedPieces); //not used??
            
            double nextSolvePercent = ValidatorObj.SfinderPercent(nextUsedPieces, CandidateCoverSequences);
            
            if (nextSolvePercent < currentSolveThresholdPercentage) continue;
            std::cout << std::fixed << std::setprecision(2);
            std::cout << "progress: " << PiecesToString(nextUsedPieces) << ", " << nextSolvePercent * 100 << "\n";

            PercentageRecordObj.AddNewPercentage(nextUsedPieces, nextSolvePercent);
            CommonFieldTree result = newPool.ReturnTree(candidatePiece, SeqMapEntry.second, nextSolvePercent, SetupPieceSequence);
            if (result.SolvePercent >= 0) {
                //record to node collection by next bag pieces
                auto key = SeqMapEntry.first.substr(std::max(0, Config.GetValueInt("--visible-pieces") - Layer)); //TODO: should this be _numSetupPieces?
                bool found = false; //TODO: turn OutputNodes from vector to map?
                for (auto& node : OutputNodes) {
                    if (node.first == key) {
                        node.second.push_back(result);
                        found = true;
                    }
                }
                if (!found) {
                    OutputNodes.push_back({ key, {result} });
                }
            }
        }
        std::cout << "--End of Layer " << Layer << "--\n";
        //if there isn't at least one valid cover for the current set of sequences, it fails to completely cover, so return negative solve percentage
        int failBranches = (LoopCount + 1) - (int)OutputNodes.size();
        if (failBranches / newSeqMap.size() > (1 - Config.GetValueDouble("--tree-succeed-percentage"))) return {-1, -1, {}};
        LoopCount++;
    }
    //Termination: return all fields that cover the final queue
    return { CurrentPiece, CurrentSolvePercent, OutputNodes };
}


SetupPool::CommonFieldTree SetupPool::ReturnStartingTree(set<string> CoverSequences, double CurrentSolvePercent, string SetupPieceSequence) { //used when layer = 0
    //remove the piece used in coversequence
    map<string, set<string>> newSeqMap = CreateNewSeqMap(CoverSequences, Config.GetValueInt("--visible-pieces")); //iterate over newSeqDict.values() to get the next CoverSequences
    // for each tetromino seen in sequence, collect (pool.ReturnTree with all setups containing the piece, per candidate piece, per subset of sequence)

    auto randomIt = newSeqMap.begin();
    std::advance(randomIt, rand() % newSeqMap.size());
    string ReachablePieces = randomIt->first.substr(0, 2);
    unordered_set<Piece> possibleNextPieces;
    for (auto possibleNextPiece : ReachablePieces) {
        set<int> newPieceIndexes = TetrominoDict.at(possibleNextPiece);
        possibleNextPieces.insert(newPieceIndexes.begin(), newPieceIndexes.end());
    }

    // get union of all remaining pieces & filter pieces with same tetromino as piece
    set<Piece> candidatePieces;
    for (auto x : possibleNextPieces) {
        if (BuildCheckerObj.isBuildable(unordered_set<Piece>({x}), 0 >= Config.GetValueInt("--visible-pieces") - 3)) { //this should be vis - 3 instead of 1(as first True) for 4?
            candidatePieces.insert(x);
        }
        else {
            //std::cout << SetToString(nextUsedPieces) << " failed.\n";
        }
    }


    SetupPool newPool(Layer + 1, unordered_set<Piece>({}), BuildCheckerObj, ValidatorObj, Config, PercentageRecordObj);
    vector<CommonFieldTree> OutputNodes;
    std::cout << "candidates(" << 0 << "): " << " + " << PiecesToString(candidatePieces) << "\n";
    for (auto candidatePieceIndex : candidatePieces) {
        CommonFieldTree result = newPool.ReturnTree(candidatePieceIndex, CoverSequences, CurrentSolvePercent, SetupPieceSequence);
        if (result.SolvePercent >= 0) { //negative solve percentage set when branch is invalid
            OutputNodes.push_back(result);
        }
    }
    return { -1, CurrentSolvePercent, {{SetupPieceSequence, OutputNodes}} };
}

vector<SetupPool::CommonFieldTree> SetupPool::Start(set<string>& Sequences) {
    if (Config.GetValueInt("--visible-pieces") < 2) throw std::invalid_argument("Not enough common pieces to work with.");
    if (Config.GetValueInt("--placed-pieces") > 4) throw std::invalid_argument("Currently cannot search setups with possible skims.");

    map<string, set<string>> newSeqMap = CreateNewSeqMap(Sequences, Config.GetValueInt("--visible-pieces"));
    vector<CommonFieldTree> Output;

    SetupPool newPool(0, Field({}), BuildCheckerObj, ValidatorObj, Config, PercentageRecordObj);

    for (const auto& sequenceEntry : newSeqMap) {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Solve threshold base: " << PercentageRecordObj.BestPercentagesString() << "\n";
        std::cout << "trying: " << sequenceEntry.first << "\n";

        //double nextSolvePercent = ValidatorObj.SfinderPercent({}, sequenceEntry.second);
        //assuming 0p always passes percentage check
        Output.push_back(newPool.ReturnStartingTree(sequenceEntry.second, 1.00, sequenceEntry.first));
        PercentageRecordObj.AddToIgnoredSequences(sequenceEntry.first);
    }
    return Output;
}