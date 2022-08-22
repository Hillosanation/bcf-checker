#pragma once
#include <map>
#include <set>
#include <string>
using std::string;
using std::set;
using std::map;
using std::pair;


class PercentageRecord {
	map<string, double> BestPercentages;
	double RunningMinimum = 1.00;
	set<string> IgnoredSequences;
	set<pair<set<int>, double>> BuildPercentages;

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