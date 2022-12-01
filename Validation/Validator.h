#pragma once
#include <string>
#include <vector>
#include <set>
using std::string;
using std::vector;
using std::set;
#include <filesystem>
#include "../Misc/CommonDataTypes.h"
#include "../Settings/Configuration.h"
#include "../Field.h"

namespace fs = std::filesystem;

class Validator {

    Configuration& Config;

    vector<string> RunCommand(const string& Command, const bool& LogCommand);

    vector<string> ReturnSfinderOutput(const string& SFinderCommand);

    vector<vector<string>> SfinderCover(set<string> CoverSequences, vector<string> GluedFumens);

    //string OverwriteFumen(string Original, string Overwrite);

    vector<string> GlueFumen(const string& UngluedFumen);

    string SwapHoldHead(const string& Sequence);

public:
    Validator(Configuration& extConfig) : Config(extConfig) {};
    
    //string IndexesToFumen(set<int> Indexes, bool Colored);

    float SfinderPercent(const Field& field, const set<string>& CoverSequences);

    set<string> ReturnCoveredQueues(const Field& field, const set<string>& CoverSequences);
};