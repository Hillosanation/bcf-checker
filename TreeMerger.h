#pragma once
#include "./Misc/CommonDataTypes.h"
#include <string>
#include <vector>
using std::vector;
using std::string;

class TreeMerger {
    CommonFieldTree RecurseMergeTree(CommonFieldTree TreeA, CommonFieldTree TreeB);

    std::pair<string, vector<CommonFieldTree>> MergeNodes(std::pair<string, vector<CommonFieldTree>> NodeA, std::pair<string, vector<CommonFieldTree>> NodeB);

public:
    vector<CommonFieldTree> ReturnMergedTrees(vector<CommonFieldTree> Trees);
};

