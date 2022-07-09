#pragma once
#include <vector>
#include <set>
#include "../Conversion/FieldConverter.h"
#include "../Settings/Configuration.h"

class BuildChecker {
private:
    FieldConverter& FieldConverterObj;
    Configuration& Config;

    std::set<std::set<int>> BuildRecord;

    typedef vector<bool> BoolLine;

    bool isPieceSupported(BoolLine PieceField, BoolLine CombinedField);

    BoolLine RemoveFromField(BoolLine OriginalField, BoolLine RemoveField);

    BoolLine IntVecToBoolVec(vector<int> IntVec);

    bool isAllPiecesSupported(vector<BoolLine> SeparatedFields, BoolLine CombinedField);

public:
    BuildChecker(FieldConverter& extpFieldConverter, Configuration& Config);

    bool isBuildable(std::set<int> Indexes, bool NoRepeat);

};







