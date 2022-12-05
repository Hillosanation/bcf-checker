#include "BuildChecker.h"
#include <stdexcept>

bool BuildChecker::PieceSupported(const unordered_set<int>& PieceMinoIndex, const unordered_set<int>& CombinedMinoIndex) const {
    //if (PiecePlayField.size() != CombinedPlayField.size()) throw "Size of fields are not equal."; //not needed

    unordered_set<int> SupportingMinoIndex = CombinedMinoIndex;
    unordered_set<int> groundMinoIndex = { 40, 41, 42, 43, 44, 45, 46, 47, 48, 49 }; //from the minoIndexes of the ground in 4 line PC
    SupportingMinoIndex.insert(groundMinoIndex.begin(), groundMinoIndex.end());

    unordered_set<int> dependancyMinoIndex = PieceMinoIndex;
    //remove mino above other minos
    for (const auto& minoIndex : PieceMinoIndex) {
        dependancyMinoIndex.erase(minoIndex - 10); //equals to fieldWidth
    }

    for (const auto& minoIndex : dependancyMinoIndex) {
        if (SupportingMinoIndex.contains(minoIndex + 10)) return true; //check if there is a mino below any of the dependancy minos
    }

    return false;
}

bool BuildChecker::shouldSearch(const Field& field, bool NoRepeat) {
    //we should only search the current field if 1. it leads to other fields that we haven't yet searched and 2. it is builable
    //checking condition 1
    if (Config.GetValue<bool>("--skip-mirror") and BuildRecord.find(field.Mirror()) != BuildRecord.end()) {
        return false; //ignore if mirror was checked
    }
    if (BuildRecord.find(field) != BuildRecord.end()) {
        return false; //ignore if current was checked
    }
    else {
        if (NoRepeat) BuildRecord.insert(field);
    }

    //checking condition 2
    unordered_set<int> combinedMinoIndex = field.AsMinoIndex();
    if (combinedMinoIndex.size() != field.AsPieces().size() * 4) return false; //all pieces should not intersect

    for (const auto& piece : field.AsPieces()) {
        if (!PieceSupported(piece.AsMinoIndex(), combinedMinoIndex)) return false;
    }
    return true;
}

