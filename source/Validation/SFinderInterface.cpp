#include <stdio.h>
#include <fstream>
#include <regex>
#include <iostream>
#include <filesystem>
#include "./SFinderInterface.h"
#include "../Configuration/Configuration.h"

vector<string> SFinderInterface::RunCommand(const string& Command, const bool& LogCommand = true) const {
    string WrappedCommand = "\"" + Command + "\"";
    //std::cout << WrappedCommand << "\n";
    std::ifstream OutputStream(_popen(WrappedCommand.c_str(), "r"));
    vector<string> Output;

    string line;
    while (std::getline(OutputStream, line)) {
        Output.push_back(line);
    }
    OutputStream.close();
    return Output;
}

vector<string> SFinderInterface::ReturnSfinderOutput(const string& SFinderCommand) const {
    fs::path SFinderPath = (std::filesystem::path)(Config.GetValue<string>("--sfinder-path"));
    return RunCommand("java -jar \"" + SFinderPath.string() + "\" " + SFinderCommand, false); //TODO: unicode path support
}

vector<vector<string>> SFinderInterface::SfinderCover(unordered_set<string> CoverSequences, vector<string> GluedFumens) const {
    fs::path FieldPath = Config.WorkingDir / "temp/field_temp.txt";
    std::ofstream FieldStream(FieldPath);
    fs::path PatternPath = Config.WorkingDir / "temp/pattern_temp.txt";
    std::ofstream PatternStream(PatternPath);
    for (const auto& coverSequence : CoverSequences) {
        PatternStream << coverSequence << "\n";
    }
    for (const auto& gluedFumen : GluedFumens) {
        FieldStream << gluedFumen << "\n";
    }
    PatternStream.close();
    FieldStream.close();

    fs::path CSVFilePath = Config.WorkingDir / "temp/cover_temp.csv";
    ReturnSfinderOutput("cover -H avoid -fp \"" + FieldPath.string() + "\" -pp \"" + PatternPath.string() + "\" -d 180 -K @jstris180 -m no -M normal -P no -o \"" + CSVFilePath.string() + "\"");
    std::ifstream CSVFileStream(CSVFilePath);
    return ReadCSV(CSVFileStream);
}

vector<string> SFinderInterface::GlueFumen(const string& UngluedFumen) const {
    fs::path FumenPath = Config.WorkingDir / "temp/unglued_fumen_temp.txt";
    std::ofstream FumenStream(FumenPath);
    FumenStream << UngluedFumen << "\n";
    FumenStream.close();
    return RunCommand("node ./glueFumen.js --fp \"" + FumenPath.string() + "\" --s --so");
}

double SFinderInterface::SolvePercentage(const Field& field, const unordered_set<string>& CoverSequences) const {
    fs::path PatternPath = Config.WorkingDir / R"(temp/pattern_temp.txt)";
    std::ofstream PatternStream(PatternPath);
    for (const auto& coverSequence : CoverSequences) {
        PatternStream << coverSequence << "\n";
    }
    PatternStream.close();
    vector<string> SfinderOutput = ReturnSfinderOutput("percent -H use -t " + field.AsFumen() + " -P 1 -pp \"" + PatternPath.string() + "\" -c 4 -th -1 -td 0 -fc 0 -d 180 -K @jstris180");

    std::regex Regex(R"(success = ([\d.]+)%)");
    string Result;
    for (const auto& line : SfinderOutput) {
        std::smatch RegexMatch;
        if (std::regex_search(line, RegexMatch, Regex)) {
            Result = RegexMatch[1];
        }
    }
    if (Result != "") {
        return RoundToDP(std::stod(Result) / 100, 4);
    }
    else {
        throw std::runtime_error("Success percentage is not found");
    }
}

string SFinderInterface::SwapHoldHead(const string& Sequence) const {
    return Sequence.substr(1, 1) + Sequence.substr(0, 1) + Sequence.substr(2);
}

double SFinderInterface::RoundToDP(double x, int DecimalPlaces) const {
    return round(x * pow(10, DecimalPlaces)) / pow(10, DecimalPlaces);
}

unordered_set<string> SFinderInterface::CoveredQueues(const Field& field, const unordered_set<string>& CoverSequences) const {
    unordered_set<string> OutputSequences;

    unordered_set<string> ExpandedCoverSequences;
    for (auto const& sequence : CoverSequences) {
        ExpandedCoverSequences.insert(sequence);
        ExpandedCoverSequences.insert(SwapHoldHead(sequence));
    }

    vector<vector<string>> CoverData = SfinderCover(ExpandedCoverSequences, GlueFumen(field.AsFumen(true)));
    CoverData.erase(CoverData.begin());

    unordered_set<string> AcceptedSequences;
    for (const auto& CoverRow : CoverData) {
        if (std::find(CoverRow.begin() + 1, CoverRow.end(), "O") != CoverRow.end()) {
            AcceptedSequences.insert(CoverRow[0]);
        }
    }

    for (auto const& sequence : CoverSequences) {
        if ((AcceptedSequences.find(sequence) != AcceptedSequences.end()) or (AcceptedSequences.find(SwapHoldHead(sequence)) != AcceptedSequences.end())) {
            OutputSequences.insert(sequence);
        }
    }

    return OutputSequences;
};