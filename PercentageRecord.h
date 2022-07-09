#pragma once
#include <map>
#include <set>
#include <string>
using std::string;
using std::set;
using std::map;


class PercentageRecord {
	map<string, double> BestPercentages;
	double RunningMinimum = 1.00;
	set<string> IgnoredSequences;

	void UpdateMinimum();

public:
	double GetThreshold();

	void UpdatePercentage(string Key, double Value);

	void AddToIgnoredSequences(string newSequence);

	set<string> ReturnSetupSequences();

	string BestPercentagesString();
};