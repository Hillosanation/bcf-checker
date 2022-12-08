#include "BuildChecker.h"

//TODO: update BuildChecker naming, it is outdated

bool BuildChecker::ExhaustedSearchPossibilities(const Field& field, bool NoRepeat) {
    //ignore if current field was checked
    if (BuildRecord.find(field) != BuildRecord.end()) return true; 
    //ignore if mirror of field was checked
    if (Config.GetValue<bool>("--skip-mirror") and BuildRecord.find(field.Mirror()) != BuildRecord.end()) return true; 

    //new field, add to record
    if (NoRepeat) BuildRecord.insert(field);
    return false;
}

bool BuildChecker::PieceSupported(const unordered_set<int> pieceMinoIndexes, const unordered_set<int> fieldMinoIndexes) const {
    unordered_set<int> FilledMinoIndexes = fieldMinoIndexes;
    FilledMinoIndexes.insert({ 40, 41, 42, 43, 44, 45, 46, 47, 48, 49 });
    for (const auto& minoIndex : pieceMinoIndexes) {
        //piece is supported if any mino directly below it is filled
        if (fieldMinoIndexes.contains(minoIndex + 10)) { //corresponds to fieldWidth
            return true;
        }
    }
    return false;
}

set<Piece> BuildChecker::FilterExploredPieces(const Field& currentField, const set<Piece>& PossiblePieces, bool NoRepeat) {
    set<Piece> Output;

    for (const auto& piece : PossiblePieces) {
        set<Piece> newFieldPieces = currentField.AsPieces();
        newFieldPieces.insert(piece);
        Field newField(newFieldPieces);

        if (!ExhaustedSearchPossibilities(newField, NoRepeat)) Output.insert(piece);
    }
}

set<Piece> BuildChecker::SearchablePieces(const Field& currentField, const set<Piece>& PossiblePieces, bool NoRepeat) {
    set<Piece> Output;
    set<Piece> CandidatePieces = FilterExploredPieces(currentField, PossiblePieces, NoRepeat);
    unordered_set<int> FieldMinoIndex = currentField.AsMinoIndex();

    for (const auto& piece : CandidatePieces) {
        for (const auto& minoIndex : piece.AsMinoIndex()) {
            if FieldMinoIndex.contains(minoIndex) continue; //no intersections
        }
        
        unordered_set<int> combinedMinoIndex = field.AsMinoIndex();
        if (PieceSupported(piece.AsMinoIndex(), currentField.AsMinoIndex())) {
            Output.insert(piece);
        }
    }
    return Output;
}