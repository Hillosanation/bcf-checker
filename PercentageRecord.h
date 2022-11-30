#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>
using std::string;
using std::set;
using std::map;
using std::pair;
using std::vector;


class PercentageRecord {
	struct SequenceResult {
		string Sequence; //The fragment of sequence used to determine which 10/11p sequences to group together.
		double BestPercent;
	};
	vector<SequenceResult> SequenceRecord;
	//map<string, double> SequenceRecord;
	double RunningMinimum = 1.00;
	set<string> IgnoredSequences;
	struct SetupResult {
		set<int> SetupPieces;
		double SolvePercentage;
	};
	set<SetupResult> SetupRecord;

	void UpdateMinimum();

public:
	double GetThreshold();

	void UpdatePercentage(string Key, double Value);

	void AddToIgnoredSequences(string newSequence);

	set<string> ReturnSetupSequences();

	string BestPercentagesString();

	bool KnownAboveThreshold(set<int> BuildPieces);

	void AddNewPercentage(set<int> BuildPieces, double SolvePercentage);
};