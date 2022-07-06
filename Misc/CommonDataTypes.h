#pragma once
#include <vector>
#include <string>
#include <set>
#include <map>
#include <iosfwd>
using std::string;
using std::vector;
using std::map;
using std::set;

typedef int Piece;
typedef std::vector<Piece> PresentPieces;
typedef std::vector<std::vector<bool>> PlayFieldFilled; //standard is col(row(mino))

struct FuSol { //fumen + solutions (pieces in order)
	string Fumen = "";
	vector<PresentPieces> Solves = {};
};

struct PFFSol { //playfieldfilled + solutions (pieces in order)
	PlayFieldFilled PFFilled;
	vector<PresentPieces> Solves = {};
};

struct StrSol { //general struct, encompassing both structs
	string Str = "";
	vector<PresentPieces> Solves = {};

	StrSol() {};
	StrSol(const FuSol& FSol) : Str(FSol.Fumen), Solves(FSol.Solves) {};
};

struct StrFieldStrPiece { //even more general, pieces are not converted to nested array of integers immediately
	string Field;
	vector<string> Solves = {};
};

struct CommonFieldTree {
	int UsedPieceIndex;
	double SolvePercent;
	vector<std::pair<string, vector<CommonFieldTree>>> childNodes; //unordered_set<CommonFieldTree> possible?
};

char ReturnTetromino(int Index);

set<int> Range(int a, int b);

const map<char, set<int>> TetrominoDict = {
    { 'I', Range(0,37 + 1) },
    { 'L', Range(38, 121 + 1) },
    { 'J', Range(122,205 + 1) },
    { 'O', Range(206,232 + 1) },
    { 'S', Range(233,274 + 1) },
    { 'T', Range(275,358 + 1) },
    { 'Z', Range(359,400 + 1) },
};

const map<char, int> FumenIndex = {
    { 'I', 1 },
    { 'L', 2 },
    { 'J', 6 },
    { 'O', 3 },
    { 'S', 7 },
    { 'T', 5 },
    { 'Z', 4 },
};

vector<vector<string>> ReadCSV(std::ifstream& FileStream);

string PercentageMapToString(map<string, double> PercentageMap);