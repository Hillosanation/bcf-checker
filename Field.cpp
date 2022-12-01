#include "Field.h"
#include ".\Conversion\FumenConvert.h"

unordered_set<Piece> Field::AsPieces() const {
    return Pieces;
};

Field Field::Mirror() const {
    unordered_set<Piece> MirroredPieces;
    for (const auto& piece : Pieces) {
        MirroredPieces.insert(piece.Mirror());
    }
    return { MirroredPieces };
}

PlayField Field::AsPlayField(bool Colored) const {
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

        for (const auto& minoIndex : FieldPermutations[piece.AsIndex()]) {
            OutputField[minoIndex] = PieceType;
        }
    }
    return OutputField;
}

std::string Field::AsFumen(bool Colored) const {
    FumenConvert FuConv;
    FuConv.ConvertPlayField(AsPlayField(Colored));
}

bool Field::operator==(Field& rhs) const {
    return this->Pieces == rhs.AsPieces();
}