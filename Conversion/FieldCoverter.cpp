//#include "./FieldConverter.h"
//#include "../Misc/CommonDataTypes.h"
//#include <stdexcept>
//
//FieldConverter::FieldVec FieldConverter::CombineFields(FieldConverter::FieldVec Original, vector<bool> Addition, int Piece) {
//    if (Original.size() != Addition.size()) throw std::invalid_argument("Size of fields are not equal.");
//    FieldVec newField = Original;
//    for (size_t i = 0; i < Addition.size(); i++) {
//        if (Addition[i] == true) {
//            newField[i] = Piece;
//        }
//    }
//    return newField;
//}
//
//FieldConverter::FieldVec FieldConverter::IndexesToField(std::set<int> Indexes, bool Colored = false) {
//    FieldVec newField(40, 0); //TODO: throw exception when overlapping
//    //Transform FieldPerm to intVec
//    for (auto index : Indexes) {
//        int PieceType;
//        if (Colored) {
//            PieceType = FumenIndex.at(ReturnTetromino(index));
//        }
//        else {
//            PieceType = 8;
//        }
//        newField = CombineFields(newField, FieldPermutations[index], PieceType);
//    }
//    return newField;
//}