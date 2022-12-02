#pragma once
#include <set>
#include <vector>
#include <string>
#include <map>

#include "./Validation/BuildChecker.h"
#include "./Validation/Validator.h"
#include "./Settings/Configuration.h"
#include "./Misc/CommonDataTypes.h"
#include "./PercentageRecord.h"

using std::set;
using std::map;
using std::string;
using std::vector;

class SetupPool {
public:
    struct CommonFieldTree {
        Piece UsedPiece;
        double SolvePercent;
        vector<std::pair<string, vector<CommonFieldTree>>> childNodes; //unordered_set<CommonFieldTree> possible?

        CommonFieldTree& operator=(CommonFieldTree const& rhs) {
            this->UsedPiece = rhs.UsedPiece;
            this->SolvePercent = rhs.SolvePercent;
            this->childNodes = rhs.childNodes;
            return *this;
        }
    };

private:
    int Layer;
    Field PrevField;
    BuildChecker& BuildCheckerObj; //const?
    Validator& ValidatorObj; //const?
    PercentageRecord& PercentageRecordObj;
    Configuration& Config;

    map<string, set<string>> CreateNewSeqMap(const set<string>& Sequences, int SamePieces);

    void AddToSeqMap(map<string, set<string>>& Map, string Key, string Entry);

    string FieldToString(Field field);

    CommonFieldTree ReturnTree(Piece CurrentPiece, set<string> CoverSequences, double CurrentSolvePercent, string SetupPieceSequence);

public:
    CommonFieldTree ReturnStartingTree(set<string> CoverSequences, double CurrentSolvePercent, string SetupPieceSequence);

    SetupPool(int layer, Field extPrevField, BuildChecker& prevBuildCheckerObj, Validator& extValidatorObj, Configuration& extConfig, PercentageRecord& extPercentageRecordObj) :
        Layer(layer), PrevField(extPrevField), BuildCheckerObj(prevBuildCheckerObj), ValidatorObj(extValidatorObj), Config(extConfig), PercentageRecordObj(extPercentageRecordObj) {};

    vector<CommonFieldTree> Start(set<string>& Sequences);
};