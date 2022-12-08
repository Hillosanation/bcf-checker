#pragma once
#include <set>
#include <unordered_set>
#include "../Settings/Configuration.h"
#include "../Field.h"
//#include "../Misc/CommonDataTypes.h"

class BuildChecker {
private:
    const Configuration& Config;

    std::set<Field> BuildRecord;

    bool ExhaustedSearchPossibilities(const Field& field, bool NoRepeat);

    bool PieceSupported(const unordered_set<int> pieceMinoIndexes, const unordered_set<int> supportedMinoIndexes) const;

    set<Piece> FilterExploredPieces(const Field& currentField, const set<Piece>& PossiblePieces, bool NoRepeat);

public:
    BuildChecker(const Configuration& extConfig) : Config(extConfig) {};

    set<Piece> SearchablePieces(const Field& currentField, const set<Piece>& PossiblePieces, bool NoRepeat);

};