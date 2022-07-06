#pragma once
#include <set>
#include <vector>
#include <string>
#include <map>

#include "./Validation/BuildChecker.h"
#include "./Validation/Validator.h"
#include "./Settings/Configuration.h"
#include "./Misc/CommonDataTypes.h"

using std::set;
using std::map;
using std::string;
using std::vector;

class SetupPoolWithoutCover {
    // does not narrow down search with the piece indexes seen in the cover, but rather calls sfinder directly.
    // as a result, FieldIndex and CoverDict are absent
private:
    int Layer;
    set<int> UsedPieceIndexes;
    BuildChecker& BuildCheckerObj; //const?
    Validator& ValidatorObj; //const?
    map<string, double>& BestPercentages;
    Configuration& Config;

    map<string, set<string>> CreateNewSeqMap(const set<string>& Sequences, int SamePieces);

    void AddToSeqMap(map<string, set<string>>& Map, string Key, string Entry);

    string SetToString(set<int> s);

    CommonFieldTree ReturnTree(int CurrentPieceIndex, set<string> CoverSequences, double CurrentSolvePercent, string SetupPieceSequence);

    double RoundToDP(double x, int DecimalPlaces);

public:
    SetupPoolWithoutCover(int layer, set<int> usedPieceIndexes, BuildChecker& prevBuildCheckerObj, Validator& extValidatorObj, map<string, double>& extBestPercentages, Configuration& extConfig) :
        Layer(layer), UsedPieceIndexes(usedPieceIndexes), BuildCheckerObj(prevBuildCheckerObj), ValidatorObj(extValidatorObj), BestPercentages(extBestPercentages), Config(extConfig) {};

    vector<CommonFieldTree> Start(set<string>& Sequences);
};