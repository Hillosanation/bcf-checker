#pragma once
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stdexcept>
#include <vector>
using std::unordered_map;
using std::unordered_set;
using std::vector;

class Piece {
    static const unordered_map<char, int> FumenIndex;

    static const unordered_map<int, char> TetrominoDict;

    static const unordered_map<int, int> MirrorMap;

    static const vector<unordered_set<int>> FieldPermutations;

	int Index;

public:
	Piece(int extIndex) : Index(extIndex) {};

    int AsIndex() const;

    Piece Mirror() const;

    char AsTetromino() const;

    int AsFumenIndex() const;

    unordered_set<int> AsMinoIndex() const;
        
    bool operator==(const Piece& rhs) const;

    Piece& operator=(const Piece& rhs) {
        this->Index = rhs.AsIndex();
        return *this;
    }

    bool operator<(const Piece& rhs) const {
        return this->Index < rhs.AsIndex();
    }

};