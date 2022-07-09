#include "./Configuration.h"
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "../Misc/CommonDataTypes.h"

void Configuration::SetConfig(vector<string> Settings, vector<vector<string>> PercentageSettings) {
	if (Settings.size() != 10) throw std::invalid_argument("Wrong amount of provided variables to set.");
	_numSetupPieces = std::stoi(Settings[0]);
	_numEqualPieces = std::stoi(Settings[1]);
	_increasedSeePiecesPerPlacement = std::stoi(Settings[2]);
	_recurseDepth = std::stoi(Settings[3]);

	SolveThresholdPercentage = std::atof(Settings[4].c_str());
	TreeSucceedPercentage = std::atof(Settings[5].c_str());

	SFinderDir = Settings[6];
	SequenceFilePath = Settings[7];
	OutputFile = Settings[8];
	SkipMirror = (bool)std::stoi(Settings[9]);
	for (const auto& entry : PercentageSettings) {
		PercentageRecordObj.UpdatePercentage(entry[0], std::stod(entry[1]));
	}
}

Configuration::Configuration(PercentageRecord& extPercentageRecordObj) : PercentageRecordObj(extPercentageRecordObj) {
	std::ifstream ConfigStream(WorkingDir / "Settings/config.txt");
	string line;
	vector<string> Settings;
	while (std::getline(ConfigStream, line)) {
		auto it = std::find(line.begin(), line.end(), '=');
		Settings.push_back(line.substr(it - line.begin() + 1));
	}
	std::ifstream BestPercentageStream(WorkingDir / "Settings/Best_Percentages.txt");
	SetConfig(Settings, ReadCSV(BestPercentageStream));
}
