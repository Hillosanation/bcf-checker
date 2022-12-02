#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;
#include "../Misc/CommonDataTypes.h"
#include "../Field.h"
#include <stdexcept>

class FumenConvert { //implementing fumen conversion natively
private: 

	struct TBoardInfo {
		int FumenIndex;
		int Consecutive;

		TBoardInfo(int extBlockNum, int extConsecutive) : FumenIndex(extBlockNum + 8), Consecutive(extConsecutive - 1) {}; //convert to the storage format instead of the actual values

		TBoardInfo(const TBoardInfo& other) : FumenIndex(other.FumenIndex), Consecutive(other.Consecutive) {};

		~TBoardInfo() {};

		TBoardInfo& operator+=(TBoardInfo& rhs) {
			if (this->FumenIndex != rhs.FumenIndex) throw std::invalid_argument("TBoardInfo cannot be added.");
			this->Consecutive += rhs.Consecutive + 1;
			return *this;
		}
	};
	typedef vector<TBoardInfo> TBoard;
	const int FieldWidth = 10;
	const std::string FumenString = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; //weird that this isn't just ascii tbh

	TBoard MakePartialBoardRepresentation(const PlayField& PFFLine);

	TBoard MakeBoardRepresentation(const PlayField& PFLine);

	std::vector<int> ConvertTo64(TBoard Board);

	std::string IntVecToFuString(std::vector<int> IntVec);

	void test_FieldToFumen();

	//std::string TrimFumen(std::string Fumen);

	//std::vector<int> StringToIntVec(std::string Fumen);

	//TBoard IntVecToBoard(std::vector<int> IntVecRep);

	//PlayFieldFilled BoardToPFF(TBoard BoardRep);

	//PlayFieldFilled RemoveExtraRows(PlayFieldFilled FilledField);

	//PlayFieldFilled GetSection(PlayFieldFilled PFFilled, int height, int width);

	//void test_FumenToField();

public:
	std::string ConvertPlayField(PlayField PlayField);

	//PlayFieldFilled ConvertFumen(std::string Fumen, int height, int width);

};