#include <iostream>
#include <stdexcept>
#include "./SetupPool.h"

double SetupPoolWithoutCover::RoundToDP(double x, int DecimalPlaces) {
    return round(x * pow(10, DecimalPlaces)) / pow(10, DecimalPlaces);
}

map<string, set<string>> SetupPoolWithoutCover::CreateNewSeqMap(const set<string>& Sequences, int SamePieces) {
    map<string, set<string>> NewSeqMap = {};
    for (auto Queue : Sequences) {
        AddToSeqMap(NewSeqMap, Queue.substr(0, SamePieces), Queue);
    }
    return NewSeqMap;
}

void SetupPoolWithoutCover::AddToSeqMap(map<string, set<string>>& Map, string Key, string Entry) {
    auto MapIter = Map.find(Key);
    if (MapIter != Map.end()) {
        Map[Key].insert(Entry);
    }
    else {
        Map[Key] = { Entry };
    }
}

string SetupPoolWithoutCover::SetToString(set<int> s) {
    string Content = "";
    for (auto i : s) {
        string newString = std::to_string(i) + ", ";
        Content.insert(Content.end(), newString.begin(), newString.end());
    }
    return "{" + Content.substr(0,Content.size()-2) + "}";
}

CommonFieldTree SetupPoolWithoutCover::ReturnTree(int CurrentPieceIndex, set<string> CoverSequences, double CurrentSolvePercent, string SetupPieceSequence) { //TODO: setup SetupPieceSequence should really be initialized from the SetupPool constructor, but then I would need to use multiple SetupPools at Start() to assign the correct setup sequence to each pool.
    set<int> AllUsedPieceIndexes;
    if (Layer >= 1) {
        AllUsedPieceIndexes = UsedPieceIndexes;
        AllUsedPieceIndexes.insert(CurrentPieceIndex);
        if (AllUsedPieceIndexes == set<int>()) throw std::runtime_error("There should be at least one used piece.");
    }

    if (Layer == Config._recurseDepth) {
        std::cout << "New setup found: " << SetToString(AllUsedPieceIndexes) << "\n";
        set<string> SetupSequences = PercentageRecordObj.ReturnSetupSequences();
        for (const auto & sequence : ValidatorObj.ReturnCoveredQueues(AllUsedPieceIndexes, SetupSequences)) {
            PercentageRecordObj.UpdatePercentage(sequence, RoundToDP(CurrentSolvePercent, 4));
        };
        
        std::cout << "Current best: " << PercentageRecordObj.BestPercentagesString() << "\n";
        
        //print out the global array of percentage each time a better field is found
        //"current best for each sequence: ..."
        string Fumen = ValidatorObj.IndexesToFumen(AllUsedPieceIndexes, true);
        std::cout << Fumen << "\n";
        return { CurrentPieceIndex, CurrentSolvePercent, {{Fumen, {}}} }; //format abuse, only leaves will hve empty vector of trees
    }

    int NumSamePieces = Config._numSetupPieces + Config._numEqualPieces + (Config._increasedSeePiecesPerPlacement - 1) * Layer;
    //remove the piece used in coversequence
    set<string> newCoverSequences;
    if (Layer >= 1) {
        for (auto sequence : CoverSequences) {
            auto pos = sequence.find(ReturnTetromino(CurrentPieceIndex));
            if (pos == std::string::npos) throw std::runtime_error("Piece to remove from sequence does not exist.");
            newCoverSequences.insert(sequence.replace(pos, 1, ""));
        }
    }
    else {
        newCoverSequences = CoverSequences;
    }
    map<string, set<string>> newSeqMap = CreateNewSeqMap(newCoverSequences, NumSamePieces); //iterate over newSeqDict.values() to get the next CoverSequences
    // for each tetromino seen in sequence, collect (pool.ReturnTree with all setups containing the piece, per candidate piece, per subset of sequence)

    //ReachablePieces = list(newCoverSequences)[0][:2]
    auto randomIt = newSeqMap.begin();
    std::advance(randomIt, rand() % newSeqMap.size());
    string ReachablePieces = randomIt->first.substr(0, 2); //only applies when there is one key in SeqDict
    set<int> possibleNextPieceIndexes;
    for (auto possibleNextPiece : ReachablePieces) {
        set<int> newPieceIndexes = TetrominoDict.at(possibleNextPiece);
        possibleNextPieceIndexes.insert(newPieceIndexes.begin(), newPieceIndexes.end());
    }
    for (const auto usedPieceIndex : AllUsedPieceIndexes) {
        possibleNextPieceIndexes.erase(usedPieceIndex);
    }

    // get union of all remaining pieceIndexes& filter pieces with same tetromino as piece
    set<int> candidatePieceIndexes;
    for (auto x : possibleNextPieceIndexes) {
        set<int> nextUsedPieceIndexes = AllUsedPieceIndexes;
        nextUsedPieceIndexes.insert(x);
        if (BuildCheckerObj.isBuildable(nextUsedPieceIndexes, Layer != 0)) {
            candidatePieceIndexes.insert(x);
        }
        else {
            //std::cout << SetToString(nextUsedPieceIndexes) << " failed.\n";
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
    //    candidatePieceIndexes.erase(i);
    //}


    SetupPoolWithoutCover newPool(Layer + 1, AllUsedPieceIndexes, BuildCheckerObj, ValidatorObj, Config, PercentageRecordObj);
    if (Layer == 0) {
        vector<CommonFieldTree> OutputNodes;
        std::cout << "candidates(" << Layer << "): " << SetToString(AllUsedPieceIndexes) << " + " << SetToString(candidatePieceIndexes) << "\n";
        for (auto candidatePieceIndex : candidatePieceIndexes) {
            CommonFieldTree result = newPool.ReturnTree(candidatePieceIndex, CoverSequences, CurrentSolvePercent, SetupPieceSequence);
            if (result.SolvePercent >= 0) { //negative solve percentage set when branch is invalid
                OutputNodes.push_back(result);
            }
        }
        return { -1, CurrentSolvePercent, {{SetupPieceSequence, OutputNodes}}};
    }
    else {
        //eliminate unbuildable fields from candidates
        //candidatePieceIndexes = {candidateIndex for candidateIndex in candidatePieceIndexes if self.ValidatorObj.PossibleToBuildv2(AllUsedPieceIndexes | {candidateIndex})} #debug

        //only call recursion for sequences with full cover with the picked PieceIndex
        vector<std::pair<string, vector<CommonFieldTree>>> OutputNodes;
        int LoopCount = 0;
        for (const auto& SeqMapEntry : newSeqMap) {
            std::cout << "candidates(" << Layer << "): " << SetToString(AllUsedPieceIndexes) << " + " << SetToString(candidatePieceIndexes) << "\n";
            for (auto candidatePieceIndex : candidatePieceIndexes) {
                //filter out fields that do not cover the current sequences
                set<int> nextUsedPieceIndexes = AllUsedPieceIndexes;
                nextUsedPieceIndexes.insert(candidatePieceIndex);

                set<string> CandidateCoverSequences;
                for (auto sequence : newCoverSequences) {
                    auto pos = sequence.find(ReturnTetromino(candidatePieceIndex));
                    if (pos == std::string::npos) throw std::runtime_error("Piece to remove from sequence does not exist.");
                    CandidateCoverSequences.insert(sequence.replace(pos, 1, ""));
                }

                //std::cout << "trying: " << SetToString(nextUsedPieceIndexes) << "\n";
                double nextSolvePercent = ValidatorObj.SfinderPercent(nextUsedPieceIndexes, CandidateCoverSequences);
                //std::cout << nextSolvePercent;
                double currentSolveThresholdPercentage = PercentageRecordObj.GetThreshold();
                //std::cout << RoundToDP(nextSolvePercent, 4)*100 << " " << RoundToDP(currentSolveThresholdPercentage, 4)*100 << "\n";
                
                if (RoundToDP(nextSolvePercent, 4) < RoundToDP(currentSolveThresholdPercentage, 4)) continue;
                std::cout << std::fixed << std::setprecision(2);
                std::cout << "progress: " << SetToString(nextUsedPieceIndexes) << ", " << nextSolvePercent * 100 << "\n";

                CommonFieldTree result = newPool.ReturnTree(candidatePieceIndex, SeqMapEntry.second, nextSolvePercent, SetupPieceSequence);
                if (result.SolvePercent >= 0) {
                    //record to node collection by next bag pieces
                    auto key = SeqMapEntry.first.substr(std::max(0, Config._numSetupPieces - Layer));
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
            if (failBranches / newSeqMap.size() > (1 - Config.TreeSucceedPercentage)) return { -1, -1, {} };
            LoopCount++;
        }
        //Termination: return all fields that cover the final queue
        return { CurrentPieceIndex, CurrentSolvePercent, OutputNodes };
    }
}

vector<CommonFieldTree> SetupPoolWithoutCover::Start(set<string>& Sequences) {
        if (Config._numSetupPieces + Config._numEqualPieces < 2) throw std::invalid_argument("Not enough common pieces to work with.");
        map<string, set<string>> newSeqMap = CreateNewSeqMap(Sequences, Config._numSetupPieces + Config._numEqualPieces);
        vector<CommonFieldTree> Output;

        for (const auto& sequenceEntry : newSeqMap) {
            PercentageRecordObj.UpdatePercentage(sequenceEntry.first, Config.SolveThresholdPercentage);
        }

        SetupPoolWithoutCover newPool(Layer + 1, {}, BuildCheckerObj, ValidatorObj, Config, PercentageRecordObj);

        for (const auto& sequenceEntry : newSeqMap) {
            std::cout << std::fixed << std::setprecision(2);
            std::cout << "Solve threshold base: " << PercentageRecordObj.BestPercentagesString() << "\n";
            std::cout << "trying: " << sequenceEntry.first << "\n";

            //double nextSolvePercent = ValidatorObj.SfinderPercent({}, sequenceEntry.second);
            //assuming 0p always passes percentage check
            double nextSolvePercent = 1.00;
            if (nextSolvePercent < PercentageRecordObj.GetThreshold()) continue;
            Output.push_back(newPool.ReturnTree({}, sequenceEntry.second, nextSolvePercent, sequenceEntry.first));
            PercentageRecordObj.AddToIgnoredSequences(sequenceEntry.first);
        }
        return Output;
    }