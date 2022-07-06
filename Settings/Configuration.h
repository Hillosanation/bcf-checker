#pragma once
#include <set>
#include <map>
#include <string>
#include <stdexcept>
#include <filesystem>
#include <vector>
using std::set;
using std::map;
using std::string;
using std::vector;

class Configuration { //TODO: global singleton?
	void SetConfig(vector<string> Settings);

public:
	int _numSetupPieces = 4;
	int _numEqualPieces = 0;
	int _increasedSeePiecesPerPlacement = 0; // usually set to 1, as you see 1 new piece from the next bag for each piece you place.
	//remaining pieces are "blind", you have to conform to the constraints

	int _recurseDepth = 4; //the number of pieces placed

	double SolveThresholdPercentage = 0.8282; //the percentage of queues that a node should at least cover
	double TreeSucceedPercentage = 0.1; //include current tree if it contains at least this percentage of maximum child nodes

	bool SkipMirror = false; //does not check mirror setups, only useful when exact mirrors can be built

	std::filesystem::path SFinderDir = R"(****)";
	const std::filesystem::path WorkingDir = std::filesystem::current_path();
	//FullBag = { "T", "I", "O", "J", "L", "S", "Z" }
	string SequenceFilePath = "input/sequence.txt";
	string OutputFile = "congruent_output_SO-TJ.txt";

	Configuration();
};
