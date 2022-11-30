#include "Field.h"
PlayField Field::AsPlayField(bool Colored = false) const {
    PlayField OutputField(40, 0); //TODO: throw exception when overlapping
    //Transform FieldPerm to intVec
    for (const auto& piece : Pieces) {
        int PieceType;
        if (Colored) {
            PieceType = piece.AsFumenIndex();
        }
        else {
            PieceType = 8;
        }

        for (size_t i = 0; i < OutputField.size(); i++) {
            OutputField[i] = FieldPermutations[piece.AsIndex()][i] * PieceType;
        }
    }
    return OutputField;
}
