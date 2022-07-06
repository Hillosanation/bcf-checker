#pragma once
#include <vector>
#include <set>
#include "../Conversion/FieldConverter.h"

class BuildChecker {
private:
    FieldConverter& FieldConverterObj;

    std::set<std::set<int>> BuildRecord;

    typedef vector<bool> BoolLine;

    bool isPieceSupported(BoolLine PieceField, BoolLine CombinedField);

    BoolLine RemoveFromField(BoolLine OriginalField, BoolLine RemoveField);

    BoolLine IntVecToBoolVec(vector<int> IntVec);

    bool isAllPiecesSupported(vector<BoolLine> SeparatedFields, BoolLine CombinedField);

public:
    BuildChecker(FieldConverter& extpFieldConverter);

    bool isBuildable(std::set<int> Indexes, bool NoRepeat);

};







