#include "BuildChecker.h"
#include "../Misc/CommonDataTypes.h"
#include <stdexcept>

using std::vector;

bool BuildChecker::isPieceSupported(BuildChecker::BoolLine PieceField, BuildChecker::BoolLine CombinedField) {
    if (PieceField.size() != CombinedField.size()) throw "Size of fields are not equal.";
    for (size_t i = 0; i < PieceField.size(); i++) {
        if ((PieceField[i] == true) && (CombinedField[i] == true)) return true;
    }
    return false;
}

BuildChecker::BoolLine BuildChecker::RemoveFromField(BuildChecker::BoolLine OriginalField, BuildChecker::BoolLine RemoveField) {
    if (OriginalField.size() != RemoveField.size()) throw "Size of fields are not equal.";
    BuildChecker::BoolLine newField = OriginalField;
    for (size_t i = 0; i < OriginalField.size(); i++) {
        if (RemoveField[i] == true) {
            newField[i] = false;
        }
    }
    return newField;
}

bool BuildChecker::isAllPiecesSupported(vector<BuildChecker::BoolLine> SeparatedFields, BuildChecker::BoolLine CombinedField) {
    CombinedField.insert(CombinedField.end(), { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 });

    vector<BoolLine> DependancyFields(SeparatedFields.size());
    for (size_t i = 0; i < SeparatedFields.size(); i++) {
        BoolLine left = SeparatedFields[i];
        left.insert(left.end(), { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
        BoolLine right = SeparatedFields[i];
        right.insert(right.begin(), { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
        DependancyFields[i] = RemoveFromField(right, left);
    }

    for (size_t i = 0; i < DependancyFields.size(); i++) {
        if (!isPieceSupported(DependancyFields[i], CombinedField)) return false;
    }
    return true;
}

BuildChecker::BoolLine BuildChecker::IntVecToBoolVec(vector<int> IntVec) {
    BoolLine Output;
    for (auto Int : IntVec) {
        Output.push_back(Int); //implicitly covert int -> bool
    }
    return Output;
}

set<int> MirrorIndexes(set<int> Indexes) {
    set<int> Output;
    for (const auto& index : Indexes) {
        Output.insert(MirrorMap.at(index));
    }
    return Output;
}

bool BuildChecker::isBuildable(std::set<int> Indexes, bool NoRepeat = true) {
    if (Config.SkipMirror and BuildRecord.find(MirrorIndexes(Indexes)) != BuildRecord.end()) {
        return false;
    }
    if (BuildRecord.find(Indexes) != BuildRecord.end()) {
        return false;
    }
    else {
        if (NoRepeat) BuildRecord.insert(Indexes);
    }

    BoolLine combinedField = IntVecToBoolVec(FieldConverterObj.IndexesToField(Indexes, false));
    if (count(combinedField.begin(), combinedField.end(), 1) != 4 * Indexes.size()) { //all pieces do not intersect
        return false;
    }

    vector<BoolLine> separatedFields;
    for (auto index : Indexes) {
        separatedFields.push_back(IntVecToBoolVec(FieldConverterObj.IndexesToField({ index }, false)));
    }
    return isAllPiecesSupported(separatedFields, combinedField);
}

BuildChecker::BuildChecker(FieldConverter& extpFieldConverter, Configuration& extConfig) : FieldConverterObj(extpFieldConverter), Config(extConfig) {}