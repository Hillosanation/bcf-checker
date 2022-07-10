#include "PercentageRecord.h"
#include <sstream>
#include <iostream> //debug

void PercentageRecord::UpdateMinimum() {
	RunningMinimum = 1.00;
	//std::cout << "Ignored: ";
	//for (auto x : IgnoredSequences) {
	//	std::cout << x << " ";
	//}
	//std::cout << "\n";
	for (const auto& entry : BestPercentages) {
		if (std::find(IgnoredSequences.begin(), IgnoredSequences.end(), entry.first) == IgnoredSequences.end()) {
			//std::cout << RunningMinimum << "<-" << entry.second << "\n";
			RunningMinimum = std::min(RunningMinimum, entry.second);
		}
	}
}

double PercentageRecord::GetThreshold() {
	return RunningMinimum;
}

void PercentageRecord::UpdatePercentage(string Key, double Value) {
	auto it = BestPercentages.find(Key);
	if (it != BestPercentages.end()) {
		BestPercentages.at(Key) = std::max(BestPercentages.at(Key), Value);
	}
	else {
		BestPercentages[Key] = Value;
	}
	UpdateMinimum();
}

void PercentageRecord::AddToIgnoredSequences(string newSequence) {
	IgnoredSequences.insert(newSequence);
	UpdateMinimum();
}

set<string> PercentageRecord::ReturnSetupSequences() {
	set<string> Output;
	for (const auto& entry : BestPercentages) {
		Output.insert(entry.first);
	}
	return Output;
}

string PercentageRecord::BestPercentagesString() {
	string Output;
	for (const auto& Entry : BestPercentages) {
		std::ostringstream tmp;
		tmp << Entry.second;
		Output += Entry.first + ": " + tmp.str() + "; ";
	}
	return "{" + Output.substr(0, Output.length() - 2) + "}";
}