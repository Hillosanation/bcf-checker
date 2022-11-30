#pragma once
#include <vector>
#include <set>
#include "../Conversion/FieldConverter.h"
#include "../Settings/Configuration.h"
#include "../PercentageRecord.h"
#include "../Field.h"
#include "../Misc/CommonDataTypes.h"

class BuildChecker {
private:
    Configuration& Config;

    std::set<Field> BuildRecord;

    bool PieceSupported(PlayField PieceField, PlayField CombinedField);

    PlayField RemoveFromField(PlayField OriginalField, PlayField RemoveField);

    bool AllPiecesSupported(vector<PlayField> SeparatedFields, PlayField CombinedField);

public:
    BuildChecker(Configuration& extConfig);

    bool isBuildable(Field field, bool NoRepeat);

};







