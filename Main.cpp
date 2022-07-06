#include "./Settings/Configuration.h"
#include "./Misc/CommonDataTypes.h"
#include "./SetupPool.h"
#include "./TreeMerger.h"
#include "./Conversion/FieldConverter.h"
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <iomanip>
#include <filesystem>
using std::set;
using std::vector;


void PrintTree(CommonFieldTree Tree, int Indent, std::ofstream& OutputStream) {
    const char tab = '\t';
    OutputStream << std::fixed << std::setprecision(2);
    if (Tree.childNodes[0].second.size() == 0) {
        OutputStream << string(Indent, tab) << Tree.UsedPieceIndex << tab << Tree.SolvePercent * 100 << "%: " << Tree.childNodes[0].first << "\n";
        return;
    }
    else {
        OutputStream << string(Indent, tab) << Tree.UsedPieceIndex << tab << Tree.SolvePercent * 100 << "%\n";
        for (const auto& Entry : Tree.childNodes) {
            for (const auto& node : Entry.second) { //ignore .first (unneeded)
                PrintTree(node, Indent + 1, OutputStream);
            }
        }
    }
}

int main() {
    //prep
    std::cout << "Begin prep\n";
    Configuration Config;
    
    set<string> Sequences;
    std::ifstream SequenceStream(Config.WorkingDir / Config.SequenceFilePath);
    for (const auto& row : ReadCSV(SequenceStream)) {
        Sequences.insert(row[0]);
    }

    //compute

    std::cout << "Begin searching for congruents\n";
    FieldConverter FieldConverterObj;
    BuildChecker BuildCheckerObj(FieldConverterObj);
    Validator ValidatorObj(FieldConverterObj, Config);
    map<string, double> BestPercentages = {};

    vector<CommonFieldTree> QueueTrees = SetupPoolWithoutCover(-1, set<int>(), BuildCheckerObj, ValidatorObj, BestPercentages, Config).Start(Sequences);

    vector<CommonFieldTree> AllTrees;
    for (const auto& tree : QueueTrees) {
        const auto& SolveTrees = tree.childNodes[0].second;
        AllTrees.insert(AllTrees.end(), SolveTrees.begin(), SolveTrees.end());
    }

    //merge

    std::cout << "Merging trees\n";
    AllTrees = TreeMerger().ReturnMergedTrees(AllTrees);
    
    //output

    std::cout << "Best chance: " << PercentageMapToString(BestPercentages) << "\n";
    std::cout << "writing: " << Config.OutputFile << "\n";

    std::ofstream OutputStream(Config.WorkingDir / Config.OutputFile);
    for (const auto& tree : AllTrees) {
        PrintTree(tree, 0, OutputStream);
    }
}
