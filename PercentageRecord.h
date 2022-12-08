#pragma once
#include <set>
#include <unordered_set>
#include <string>
#include <vector>
#include "./Field.h"
using std::string;
using std::set;
using std::unordered_set;
using std::vector;


class PercentageRecord {
	struct SequenceResult {
		string Sequence; //The fragment of sequence used to determine which 10/11p sequences to group together.
		double BestPercent;
	};
	vector<SequenceResult> SequenceRecord;
	double RunningMinimum = 1.00;
	unordered_set<string> IgnoredSequences;

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
	double GetThreshold() const;

	void UpdatePercentage(string Key, double Value);

	void AddToIgnoredSequences(string newSequence);

	unordered_set<string> SetupSequences() const;

	string BestPercentagesString() const;

	bool SetupAboveThreshold(const Field& SetupField);

	void AddNewPercentage(const Field& SetupField, double SolvePercentage);
};