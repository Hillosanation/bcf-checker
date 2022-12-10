#pragma once
#include <set>
#include <unordered_set>
#include <vector>
#include <string>
#include <unordered_map>

#include "../Validation/BuildChecker.h"
#include "../Validation/SFinderInterface.h"
#include "../Configuration/Configuration.h"
#include "../Misc/CommonDataTypes.h"
#include "../Validation/PercentageRecord.h"

using std::set;
using std::unordered_set;
using std::unordered_map;
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
    const Field PrevField;
    BuildChecker& BuildCheckerObj;
    const SFinderInterface& SFinder;
    PercentageRecord& PercentageRecordObj;
    const Configuration& Config;

    unordered_map<string, unordered_set<string>> CreateNewSeqMap(const unordered_set<string>& Sequences, int SamePieces);

    string FieldToString(const Field& field);

    CommonFieldTree ReturnTree(Piece CurrentPiece, unordered_set<string> CoverSequences, double CurrentSolvePercent, string SetupPieceSequence);

public:
    CommonFieldTree ReturnStartingTree(unordered_set<string> CoverSequences, double CurrentSolvePercent, string SetupPieceSequence);

    SetupPool(int layer, const Field extPrevField, BuildChecker& prevBuildCheckerObj, const SFinderInterface& extSFinder, const Configuration& extConfig, PercentageRecord& extPercentageRecordObj) :
        Layer(layer), PrevField(extPrevField), BuildCheckerObj(prevBuildCheckerObj), SFinder(extSFinder), Config(extConfig), PercentageRecordObj(extPercentageRecordObj) {};

    vector<CommonFieldTree> Start(const unordered_set<string>& Sequences);
};