#pragma once
#include <string>
#include <vector>
#include <unordered_set>
using std::string;
using std::vector;
using std::unordered_set;
#include <filesystem>
#include "../Misc/CommonDataTypes.h"
#include "../Settings/Configuration.h"
#include "../Field.h"

namespace fs = std::filesystem;

class SFinderInterface { //handles all calls to external programs

    const Configuration& Config;

    vector<string> RunCommand(const string& Command, const bool& LogCommand) const;

    vector<string> ReturnSfinderOutput(const string& SFinderCommand) const;

    vector<vector<string>> SfinderCover(unordered_set<string> CoverSequences, vector<string> GluedFumens) const;

    vector<string> GlueFumen(const string& UngluedFumen) const;

    string SwapHoldHead(const string& Sequence) const;

    double RoundToDP(double x, int DecimalPlaces) const;

public:
    SFinderInterface(const Configuration& extConfig) : Config(extConfig) {};

    double SolvePercentage(const Field& field, const unordered_set<string>& CoverSequences) const;

    unordered_set<string> CoveredQueues(const Field& field, const unordered_set<string>& CoverSequences) const;
};