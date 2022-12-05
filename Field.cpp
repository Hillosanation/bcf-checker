#include "Field.h"
#include ".\Conversion\FumenConvert.h"

set<Piece> Field::AsPieces() const {
    return Pieces;
};

Field Field::Mirror() const {
    set<Piece> MirroredPieces;
    for (const auto& piece : Pieces) {
        MirroredPieces.insert(piece.Mirror());
    }
    return { MirroredPieces };
}

PlayField Field::AsPlayField(bool Colored = true) const { //numbering follows fumen indexing
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

        for (const auto& minoIndex : piece.AsMinoIndex()) {
            OutputField[minoIndex] = PieceType;
        }
    }
    return OutputField;
}

std::string Field::AsFumen(bool Colored) const {
    FumenConvert FuConv;
    return FuConv.ConvertPlayField(AsPlayField(Colored));
}

bool Field::operator==(const Field& rhs) const {
    return this->Pieces == rhs.AsPieces();
}

unordered_set<int> Field::AsMinoIndex() const { //maybe get the minoIndex from the pieces instead of mangaging it from field?
    unordered_set<int> Output;
    for (const auto& piece : Pieces) {
        auto pieceMinoIndex = piece.AsMinoIndex();
        Output.insert(pieceMinoIndex.begin(), pieceMinoIndex.end());
    }
    return Output;
}