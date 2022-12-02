#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>
#include "./Field.h"
using std::string;
using std::set;
using std::map;
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
		Field SetupField;
		double SolvePercentage;

		bool operator<(const SetupResult& rhs) const {
			return (this->SetupField < rhs.SetupField) or (this->SolvePercentage < rhs.SolvePercentage);
		}
	};
	set<SetupResult> SetupRecord;

	void UpdateMinimum();

	double RoundToDP(double x, int DecimalPlaces);

public:
	double GetThreshold();

	void UpdatePercentage(string Key, double Value);

	void AddToIgnoredSequences(string newSequence);

	set<string> ReturnSetupSequences();

	string BestPercentagesString();

	bool SetupAboveThreshold(Field SetupField);

	void AddNewPercentage(Field SetupField, double SolvePercentage);
};