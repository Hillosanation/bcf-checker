#include "BuildChecker.h"
#include <stdexcept>

using std::vector;

bool BuildChecker::PieceSupported(PlayField PiecePlayField, PlayField CombinedPlayField) {
    //if (PiecePlayField.size() != CombinedPlayField.size()) throw "Size of fields are not equal."; //not needed

    PlayField upperField = PiecePlayField;
    upperField.insert(upperField.end(), { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
    PlayField lowerField = PiecePlayField;
    lowerField.insert(lowerField.begin(), { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });

    //all possible filled mino positions that can support the current piece
    PlayField DependancyField = RemoveFromField(lowerField, upperField);

    for (size_t i = 0; i < DependancyField.size(); i++) {
        if ((DependancyField[i] != 0) && (CombinedPlayField[i] != 0)) return true;
    }
    return false;
}

PlayField BuildChecker::RemoveFromField(PlayField StartingPlayField, PlayField RemovePlayField) {
    if (StartingPlayField.size() != RemovePlayField.size()) throw "Size of fields are not equal.";
    vector<int> newField = StartingPlayField;
    for (size_t i = 0; i < StartingPlayField.size(); i++) {
        if (RemovePlayField[i] != 0) {
            newField[i] = 0;
        }
    }
    return newField;
}

bool BuildChecker::AllPiecesSupported(vector<PlayField> PiecePlayFields, PlayField CombinedPlayField) {
    //the new column represents the floor
    CombinedPlayField.insert(CombinedPlayField.end(), { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 });

    for (const auto& PiecePlayField : PiecePlayFields) {
        if (!PieceSupported(PiecePlayField, CombinedPlayField)) return false;
    }
    return true;
}

bool BuildChecker::isBuildable(Field field, bool NoRepeat = true) {
    if (Config.GetValue<bool>("--skip-mirror") and BuildRecord.find(field.Mirror()) != BuildRecord.end()) {
        return false;
    }
    if (BuildRecord.find(field) != BuildRecord.end()) {
        return false;
    }
    else {
        if (NoRepeat) BuildRecord.insert(field);
    }

    vector<int> combinedPlayField = field.AsPlayField(false);
    auto NonEmptyMino = [](int MinoType) { return MinoType != 0; };
    if (std::count_if(combinedPlayField.begin(), combinedPlayField.end(), NonEmptyMino) != 4 * field.AsPieces().size()) { //all pieces do not intersect
        return false;
    }

    vector<vector<int>> piecePlayFields;
    for (const auto& piece : field.AsPieces()) {
        piecePlayFields.push_back(Field({ piece }).AsPlayField(false));
    }
    return AllPiecesSupported(piecePlayFields, combinedPlayField);
}

BuildChecker::BuildChecker(Configuration& extConfig) : Config(extConfig) {}