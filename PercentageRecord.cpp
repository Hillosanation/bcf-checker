#include "PercentageRecord.h"
#include <sstream>
#include <iostream> //debug
#include "Misc/CommonDataTypes.h"

void PercentageRecord::UpdateMinimum() {
	RunningMinimum = 1.00;
	//std::cout << "Ignored: ";
	//for (auto x : IgnoredSequences) {
	//	std::cout << x << " ";
	//}
	//std::cout << "\n";
	for (const auto& sequenceResult : SequenceRecord) {
		if (std::find(IgnoredSequences.begin(), IgnoredSequences.end(), sequenceResult.Sequence) == IgnoredSequences.end()) {
			//std::cout << RunningMinimum << "<-" << entry.second << "\n";
			RunningMinimum = std::min(RunningMinimum, sequenceResult.BestPercent);
		}
	}
}

double PercentageRecord::GetThreshold() {
	return RunningMinimum;
}

void PercentageRecord::UpdatePercentage(string Sequence, double SolvePercentage) {
	auto MatchingSequence = [Sequence](SequenceResult sequenceResult) { Sequence == sequenceResult.Sequence; };
	auto it = std::find_if(SequenceRecord.begin(), SequenceRecord.end(), MatchingSequence);
	if (it != SequenceRecord.end()) {
		it->BestPercent = std::max(it->BestPercent, SolvePercentage);
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

set<string> PercentageRecord::ReturnSetupSequences() {
	set<string> Output;
	for (const auto& sequenceResult : SequenceRecord) {
		Output.insert(sequenceResult.Sequence);
	}
	return Output;
}

string PercentageRecord::BestPercentagesString() { //non-functional
	string Output;
	for (const auto& sequenceResult : SequenceRecord) {
		std::ostringstream tmp;
		tmp << sequenceResult.BestPercent;
		Output += sequenceResult.Sequence + ": " + tmp.str() + "; ";
	}
	return "{" + Output.substr(0, Output.length() - 2) + "}";
}

bool PercentageRecord::KnownAboveThreshold(set<int> BuildPieces) {
	//remove outdated percentages while we're here
	double threshold = RoundToDP(GetThreshold(), 4);
	for (auto setup : SetupRecord) {
		if (RoundToDP(setup.SolvePercentage, 4) < threshold) {
			SetupRecord.erase(setup);
		}
	}
	auto SetupIsRecorded = [BuildPieces](SetupResult setup) {setup.SetupPieces == BuildPieces; };
	auto it = std::find_if(SetupRecord.begin(), SetupRecord.end(), SetupIsRecorded);
	return it != SetupRecord.end();
}

void PercentageRecord::AddNewPercentage(set<int> BuildPieces, double SolvePercentage) {
	if (RoundToDP(SolvePercentage, 4) >= RoundToDP(GetThreshold(), 4)) { //failsafe
		SetupRecord.insert({ BuildPieces, SolvePercentage });
	}
}