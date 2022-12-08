#include "PercentageRecord.h"
#include <sstream>
//#include <iostream> //debug

void PercentageRecord::UpdateMinimum() {
	RunningMinimum = 1.00;
	for (const auto& sequenceResult : SequenceRecord) {
		if (!IgnoredSequences.contains(sequenceResult.Sequence)) {
			//std::cout << RunningMinimum << "<-" << entry.second << "\n";
			RunningMinimum = std::min(RunningMinimum, sequenceResult.BestPercent);
		}
	}
}

double PercentageRecord::RoundToDP(double x, int DecimalPlaces) {
	return round(x * pow(10, DecimalPlaces)) / pow(10, DecimalPlaces);
}

double PercentageRecord::GetThreshold() const {
	return RunningMinimum;
}

void PercentageRecord::UpdatePercentage(string Sequence, double SolvePercentage) {
	auto MatchingSequence = [Sequence](SequenceResult sequenceResult) { return Sequence == sequenceResult.Sequence; };
	auto it = std::find_if(SequenceRecord.begin(), SequenceRecord.end(), MatchingSequence);
	if (it != SequenceRecord.end()) {
		it->BestPercent = std::max(it->BestPercent, RoundToDP(SolvePercentage,4));
	}
	else {
		SequenceRecord.push_back({ Sequence, SolvePercentage });
	}
	UpdateMinimum();
}

void PercentageRecord::AddToIgnoredSequences(string newSequence) {
	IgnoredSequences.insert(newSequence);
	UpdateMinimum();
}

unordered_set<string> PercentageRecord::SetupSequences() const {
	unordered_set<string> Output;
	for (const auto& sequenceResult : SequenceRecord) {
		Output.insert(sequenceResult.Sequence);
	}
	return Output;
}

string PercentageRecord::BestPercentagesString() const { //non-functional
	string Output;
	for (const auto& sequenceResult : SequenceRecord) {
		std::ostringstream tmp;
		tmp << sequenceResult.BestPercent;
		Output += sequenceResult.Sequence + ": " + tmp.str() + "; ";
	}
	return "{" + Output.substr(0, Output.length() - 2) + "}";
}

bool PercentageRecord::SetupAboveThreshold(const Field& setupField) { //checks if the shape is known to have a high solvepercentage, unused
	//remove outdated percentages while we're here
	double threshold = GetThreshold();
	for (auto setup : SetupRecord) {
		if (setup.SolvePercentage < threshold) {
			SetupRecord.erase(setup);
		}
	}
	auto SetupIsRecorded = [setupField](SetupResult setup) { return setup.SetupField == setupField; };
	auto it = std::find_if(SetupRecord.begin(), SetupRecord.end(), SetupIsRecorded);
	return it != SetupRecord.end();
}

void PercentageRecord::AddNewPercentage(const Field& setupField, double SolvePercentage) {
	if (SolvePercentage >= GetThreshold()) { //failsafe
		SetupRecord.insert({ setupField, SolvePercentage });
	}
}