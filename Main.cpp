#include "./Settings/Configuration.h"
#include "./Misc/CommonDataTypes.h"
#include "./PercentageRecord.h"
#include "./SetupPool.h"
#include "./TreeMerger.h"
#include "./Conversion/FieldConverter.h"
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <iomanip>
//#include <filesystem>
using std::set;
using std::vector;


void PrintTree(SetupPool::CommonFieldTree Tree, int Indent, std::ofstream& OutputStream) {
    const char tab = '\t';
    OutputStream << std::fixed << std::setprecision(2);
    if (Tree.childNodes[0].second.size() == 0) {
        OutputStream << string(Indent, tab) << Tree.UsedPiece.AsIndex()  << tab << Tree.SolvePercent * 100 << "%: " << Tree.childNodes[0].first << "\n";
        return;
    }
    else {
        OutputStream << string(Indent, tab) << Tree.UsedPiece.AsIndex() << tab << Tree.SolvePercent * 100 << "%\n";
        for (const auto& Entry : Tree.childNodes) {
            for (const auto& node : Entry.second) { //ignore .first (unneeded)
                PrintTree(node, Indent + 1, OutputStream);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    //prep
    std::cout << "Begin prep\n";
    PercentageRecord PercentageRecordObj;
    Configuration Config(PercentageRecordObj, argc, argv);
    std::cout << "Best chance: " << PercentageRecordObj.BestPercentagesString() << "\n";
    
    set<string> Sequences;
    std::ifstream SequenceStream(Config.WorkingDir / Config.GetValueString("--sequence-path"));
    for (const auto& row : ReadCSV(SequenceStream)) {
        Sequences.insert(row[0]);
    }

    //compute

    std::cout << "Begin searching for congruents\n";
    BuildChecker BuildCheckerObj(Config);
    Validator ValidatorObj(Config);

    vector<SetupPool::CommonFieldTree> QueueTrees = SetupPool(-1, Field({}), BuildCheckerObj, ValidatorObj, Config, PercentageRecordObj).Start(Sequences);

    vector<SetupPool::CommonFieldTree> AllTrees;
    for (const auto& tree : QueueTrees) {
        const auto& SolveTrees = tree.childNodes[0].second;
        AllTrees.insert(AllTrees.end(), SolveTrees.begin(), SolveTrees.end());
    }

    //merge

    //std::cout << "Merging trees\n";
    //AllTrees = TreeMerger().ReturnMergedTrees(AllTrees);
    
    //output

    std::cout << "writing: " << Config.GetValueString("--output-path") << "\n";

    std::ofstream OutputStream(Config.WorkingDir / Config.GetValueString("--output-path"));
    OutputStream << "Best chance: " << PercentageRecordObj.BestPercentagesString() << "\n";
    for (const auto& tree : AllTrees) {
        PrintTree(tree, 0, OutputStream);
    }
}
