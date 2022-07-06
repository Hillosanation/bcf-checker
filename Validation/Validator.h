#pragma once
#include <string>
#include <vector>
#include <set>
using std::string;
using std::vector;
using std::set;
#include <filesystem>
#include "../Conversion/FieldConverter.h"
#include "../Conversion/FumenConvert.h"
#include "../Misc/CommonDataTypes.h"
#include "../Settings/Configuration.h"

namespace fs = std::filesystem;

class Validator {

    FieldConverter& FieldConverterObj;

    FumenConvert FumenConvertObj;

    Configuration& Config;

    vector<string> RunCommand(string Command, bool LogCommand);

    vector<string> ReturnSfinderOutput(string SFinderCommand);

    vector<vector<string>> SfinderCover(set<string> CoverSequences, vector<string> GluedFumens);

    string OverwriteFumen(string Original, string Overwrite);

    vector<string> GlueFumens(vector<string> UngluedFumens);

    string SwapHoldHead(string Sequence);

public:
    Validator(FieldConverter& extFieldConverterObj, Configuration& extConfig) : FieldConverterObj(extFieldConverterObj), Config(extConfig) {};
    
    string IndexesToFumen(set<int> Indexes, bool Colored);

    float SfinderPercent(set<int> UsedPieceIndexes, set<string> CoverSequences);

    set<string> ReturnCoveredQueues(set<int> PieceIndexes, set<string> CoverSequences);
};