#include <iostream>
#include <stdexcept>
#include "./SetupPool.h"
#include "./Field.h"

unordered_map<string, unordered_set<string>> SetupPool::CreateNewSeqMap(const unordered_set<string>& Sequences, int SamePieces) {
    unordered_map<string, unordered_set<string>> NewSeqMap = {};
    for (auto Queue : Sequences) {
        string SequenceHead = Queue.substr(0, SamePieces);

        if (NewSeqMap.contains(SequenceHead)) {
            NewSeqMap[SequenceHead].insert(Queue);
        }
        else {
            NewSeqMap[SequenceHead] = { Queue };
        }
    }
    return NewSeqMap;
}

string SetupPool::FieldToString(const Field& field) { //cosmetic feature
    string Content = "";
    for (const auto& piece : field.AsPieces()) {
        string newString = std::to_string(piece.AsIndex()) + ", ";
        Content.insert(Content.end(), newString.begin(), newString.end());
    }
    return "{" + Content.substr(0,Content.size()-2) + "}";
}

SetupPool::CommonFieldTree SetupPool::ReturnTree(Piece CurrentPiece, unordered_set<string> CoverSequences, double CurrentSolvePercent, string SetupPieceSequence) { //TODO: setup SetupPieceSequence should really be initialized from the SetupPool constructor, but then I would need to use multiple SetupPools at Start() to assign the correct setup sequence to each pool.
    set<Piece> CurrentUsedPieces = PrevField.AsPieces();
    CurrentUsedPieces.insert(CurrentPiece);
    Field CurrentField(CurrentUsedPieces);

    if (Layer == Config.GetValue<int>("--placed-pieces")) {
        std::cout << "New setup found: " << FieldToString(CurrentField) << "\n";
        for (const auto& sequence : SFinder.CoveredQueues(CurrentField, PercentageRecordObj.SetupSequences())) {
            PercentageRecordObj.UpdatePercentage(sequence, CurrentSolvePercent);
        };
        
        std::cout << "Current best: " << PercentageRecordObj.BestPercentagesString() << "\n";
        
        //print out the global array of percentage each time a better field is found
        //"current best for each sequence: ..."
        string Fumen = CurrentField.AsFumen();
        std::cout << Fumen << "\n";
        return { CurrentPiece, CurrentSolvePercent, {{Fumen, {}}} }; //format abuse, only leaves will have empty vector of trees
    }

    int NumSamePieces = Config.GetValue<int>("--visible-pieces") + (Config.GetValue<int>("--increased-vision") - 1) * Layer;
    //remove the piece used in coversequence
    unordered_set<string> newCoverSequences;
    for (auto sequence : CoverSequences) {
        auto pos = sequence.find(CurrentPiece.AsTetromino());
        if (pos == std::string::npos) throw std::runtime_error("Piece to remove from sequence does not exist.");
        newCoverSequences.insert(sequence.replace(pos, 1, ""));
    }
    unordered_map<string, unordered_set<string>> newSeqMap = CreateNewSeqMap(newCoverSequences, NumSamePieces); //iterate over newSeqDict.values() to get the next CoverSequences
    // for each tetromino seen in sequence, collect (pool.ReturnTree with all setups containing the piece, per candidate piece, per subset of sequence)

    auto randomIt = newSeqMap.begin(); //TODO: this method of getting the truncated letters probably shouldn't be used anyways
    std::advance(randomIt, rand() % newSeqMap.size());
    string ReachableTetrominos = randomIt->first.substr(0, 2);
    set<Piece> possibleNextPieces;
    for (const auto& possibleTetromino : ReachableTetrominos) {
        unordered_set<int> newPieceIndexes = PieceIndexesWithTetromino.at(possibleTetromino);
        possibleNextPieces.insert(newPieceIndexes.begin(), newPieceIndexes.end());
    }
    for (const auto& usedPiece : CurrentField.AsPieces()) {
        possibleNextPieces.erase(usedPiece);
    }

    //TODO: build checker can shoulder the job of filtering out all pieces, and take in PieceIndexesWithTetromino in its class instead of making setupPool do it.
    set<Piece> candidatePieces = BuildCheckerObj.SearchablePieces(CurrentField, possibleNextPieces, Layer >= Config.GetValue<int>("--visible-pieces") - 3);
    
    //manual pruning
    //set<Piece> r;
    //if (Layer == 1) {
    //    r = { 16, 17, 18, 19, 20, 21, 22, 28, 29, 30, 31, 32, 37, 133, 134, 135, 136, 137, 138, 139, 140, 151, 152, 153, 154, 155, 156, 157, 158, 159, 175, 176, 177, 178, 180, 181, 182, };
    //} if (Layer == 2) {
    //    r = { 11, 12, 13, 16, 17, 21, 22, };
    //} if (Layer == 3) {
    //    r = { 43, 44, 45, 49, 50, 54, 55, 56, };
    //}
    //for (auto i : r) {
    //    candidatePieces.erase({ i });
    //}



    SetupPool newPool(Layer + 1, CurrentField, BuildCheckerObj, SFinder, Config, PercentageRecordObj);
    //eliminate unbuildable fields from candidates

    //only call recursion for sequences with full cover with the picked PieceIndex
    vector<std::pair<string, vector<CommonFieldTree>>> OutputNodes;
    int LoopCount = 0;
    for (const auto& SeqMapEntry : newSeqMap) {
        std::cout << "candidates(" << Layer << "): " << FieldToString(CurrentField) << " + " << candidatePieces.size() << "\n";
        //std::cout << "candidates(" << Layer << "): " << FieldToString(CurrentField) << " + " << candidatePieces.size() << "\n";
        for (auto candidatePiece : candidatePieces) {
            //filter out fields that do not cover the current sequences
            //std::cout << candidatePiece.AsIndex() << "\n";
            set<Piece> nextUsedPieces = CurrentField.AsPieces();
            nextUsedPieces.insert(candidatePiece);

            unordered_set<string> CandidateCoverSequences;
            for (auto sequence : newCoverSequences) {
                auto pos = sequence.find(candidatePiece.AsTetromino());
                if (pos == std::string::npos) throw std::runtime_error("Piece to remove from sequence does not exist.");
                CandidateCoverSequences.insert(sequence.replace(pos, 1, ""));
            }
            
            //shortcut re-checking percentages already confirmed by sfinder
            double currentSolveThresholdPercent = PercentageRecordObj.GetThreshold();
            //bool AboveThreshold = PercentageRecordObj.SetupAboveThreshold(nextUsedPieces); //not used??
            //TODO: re-use this function, iirc it records the setups that are in-between the two best perentages, so that we know that that combination works already
            
            //TODO: do these in bulk and process the percentages later, not right after one finishes
            // this can make the bottom half of the loop slide off the nested loops
            
            double nextSolvePercent = SFinder.SolvePercentage(nextUsedPieces, CandidateCoverSequences);
            //std::cout << nextSolvePercent*100 << " < " << currentSolveThresholdPercent*100 << (nextSolvePercent < currentSolveThresholdPercent) << "\n";

            if (nextSolvePercent < currentSolveThresholdPercent) continue;
            std::cout << std::fixed << std::setprecision(2);
            std::cout << "progress     : " << FieldToString(nextUsedPieces) << ", " << nextSolvePercent*100 << "\n";

            PercentageRecordObj.AddNewPercentage(nextUsedPieces, nextSolvePercent);
            CommonFieldTree result = newPool.ReturnTree(candidatePiece, SeqMapEntry.second, nextSolvePercent, SetupPieceSequence);
            if (result.SolvePercent >= 0) {
                //record to node collection by next bag pieces
                auto key = SeqMapEntry.first.substr(std::max(0, Config.GetValue<int>("--visible-pieces") - Layer)); //TODO: should this be _numSetupPieces?
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
        if (failBranches / newSeqMap.size() > (1 - Config.GetValue<double>("--tree-succeed-percentage"))) return {-1, -1, {}};
        LoopCount++;
    }
    //Termination: return all fields that cover the final queue
    return { CurrentPiece, CurrentSolvePercent, OutputNodes };
}


SetupPool::CommonFieldTree SetupPool::ReturnStartingTree(unordered_set<string> CoverSequences, double CurrentSolvePercent, string SetupPieceSequence) { //used when layer = 0
    //remove the piece used in coversequence
    unordered_map<string, unordered_set<string>> newSeqMap = CreateNewSeqMap(CoverSequences, Config.GetValue<int>("--visible-pieces")); //iterate over newSeqDict.values() to get the next CoverSequences
    // for each tetromino seen in sequence, collect (pool.ReturnTree with all setups containing the piece, per candidate piece, per subset of sequence)

    auto randomIt = newSeqMap.begin();
    std::advance(randomIt, rand() % newSeqMap.size());
    string ReachablePieces = randomIt->first.substr(0, 2);
    set<Piece> possibleNextPieces;
    for (auto possibleNextPiece : ReachablePieces) {
        unordered_set<int> newPieceIndexes = PieceIndexesWithTetromino.at(possibleNextPiece);
        possibleNextPieces.insert(newPieceIndexes.begin(), newPieceIndexes.end());
    }

    set<Piece> candidatePieces = BuildCheckerObj.SearchablePieces(Field({}), possibleNextPieces, false);

    //manual pruning
    //for (auto i : { 21, 22, 23, 24, 25, }) {
    //    candidatePieces.erase({ i });
    //}

    SetupPool newPool(Layer + 1, Field({}), BuildCheckerObj, SFinder, Config, PercentageRecordObj);
    vector<CommonFieldTree> OutputNodes;
    std::cout << "candidates(" << 0 << "): " << " + " << FieldToString(candidatePieces) << "\n";
    for (auto candidatePieceIndex : candidatePieces) {
        CommonFieldTree result = newPool.ReturnTree(candidatePieceIndex, CoverSequences, CurrentSolvePercent, SetupPieceSequence);
        if (result.SolvePercent >= 0) { //negative solve percentage set when branch is invalid
            OutputNodes.push_back(result);
        }
    }
    return { -1, CurrentSolvePercent, {{SetupPieceSequence, OutputNodes}} };
}

vector<SetupPool::CommonFieldTree> SetupPool::Start(const unordered_set<string>& Sequences) {
    if (Config.GetValue<int>("--visible-pieces") < 2) throw std::invalid_argument("Not enough common pieces to work with.");
    if (Config.GetValue<int>("--placed-pieces") > 4) throw std::invalid_argument("Currently cannot search setups with possible skims.");

    unordered_map<string, unordered_set<string>> newSeqMap = CreateNewSeqMap(Sequences, Config.GetValue<int>("--visible-pieces"));
    vector<CommonFieldTree> Output;

    SetupPool newPool(0, Field({}), BuildCheckerObj, SFinder, Config, PercentageRecordObj);

    for (const auto& sequenceEntry : newSeqMap) {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Solve threshold base: " << PercentageRecordObj.BestPercentagesString() << "\n";
        std::cout << "trying: " << sequenceEntry.first << "\n";

        //double nextSolvePercent = SFinder .SfinderPercent({}, sequenceEntry.second);
        //it takes too long to check 1p, assuming 1p always passes percentage check
        Output.push_back(newPool.ReturnStartingTree(sequenceEntry.second, 1.00, sequenceEntry.first));
        PercentageRecordObj.AddToIgnoredSequences(sequenceEntry.first);
    }
    return Output;
}