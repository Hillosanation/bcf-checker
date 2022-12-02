#pragma once
#include <set>
#include <map>
#include <vector>
#include ".\Piece.h"
#include ".\Misc\CommonDataTypes.h"
using std::set;
using std::map;
using std::vector;

class Field //Handles all representations of a field
{
	const set<Piece> Pieces;

    static const vector<vector<int>> FieldPermutations;

public:
	Field(set<Piece> extPieces) : Pieces(extPieces) {};

    set<Piece> AsPieces() const;

    Field Mirror() const;

    PlayField AsPlayField(bool Colored = false) const;

    std::string AsFumen(bool Colored = false) const;

    bool operator==(const Field& rhs) const;
	
    bool operator<(const Field& rhs) const {
        return this->Pieces < rhs.AsPieces();
    }
};
