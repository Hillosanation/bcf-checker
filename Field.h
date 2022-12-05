#pragma once
#include <unordered_set>
#include <set>
#include <vector>
#include ".\Piece.h"
#include ".\Misc\CommonDataTypes.h"
using std::unordered_set;
using std::vector;
using std::set;

class Field //Handles all representations of a field
{
	const set<Piece> Pieces;

    PlayField AsPlayField(bool Colored) const;

public:
	Field(set<Piece> extPieces) : Pieces(extPieces) {};

    set<Piece> AsPieces() const;

    Field Mirror() const;

    unordered_set<int> AsMinoIndex() const;

    std::string AsFumen(bool Colored = true) const;

    bool operator==(const Field& rhs) const;
	
    bool operator<(const Field& rhs) const {
        return this->Pieces < rhs.AsPieces();
    }
};
