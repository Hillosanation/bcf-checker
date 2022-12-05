#pragma once
#include <set>
#include <unordered_set>
#include "../Settings/Configuration.h"
#include "../Field.h"
#include "../Misc/CommonDataTypes.h"

class BuildChecker {
private:
    const Configuration& Config;

    std::set<Field> BuildRecord;

    bool PieceSupported(const unordered_set<int>& PieceMinoIndex, const unordered_set<int>& CombinedMinoIndex) const;

public:
    BuildChecker(const Configuration& extConfig) : Config(extConfig) {};

    bool shouldSearch(const Field& field, bool NoRepeat = true);

};







