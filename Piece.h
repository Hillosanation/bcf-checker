#pragma once
#include <map>
#include <set>
#include <stdexcept>
using std::map;
using std::set;

class Piece {
    static const map<char, int> FumenIndex;

    static const map<int, char> TetrominoDict;

    static const map<int, int> MirrorMap;

	int Index;

public:
	Piece(int extIndex) : Index(extIndex) {};

    int AsIndex() const;

    Piece Mirror() const;

    char AsTetromino() const;

    int AsFumenIndex() const;
        
    bool operator==(const Piece& rhs) const;

    Piece& operator=(const Piece& rhs) {
        this->Index = rhs.AsIndex();
        return *this;
    }

    bool operator<(const Piece& rhs) const {
        return this->Index < rhs.AsIndex();
    }

};