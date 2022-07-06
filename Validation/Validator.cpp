#include <stdio.h>
#include <fstream>
#include <regex>
#include "./Validator.h"
#include <iostream>

vector<string> Validator::RunCommand(string Command, bool LogCommand = true) {
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

vector<string> Validator::ReturnSfinderOutput(string SFinderCommand) {
        fs::path SFinderPath = Config.SFinderDir / "sfinder-fixed-180.jar";
        return RunCommand("java -jar \"" + SFinderPath.string() + "\" " + SFinderCommand, false); //TODO: unicode path support
    }

string Validator::IndexesToFumen(std::set<int> Indexes, bool Colored = false) { 
    FieldConverter::FieldVec Field = FieldConverterObj.IndexesToField(Indexes, Colored);
    return FumenConvertObj.ConvertPFLine(Field);
}

vector<vector<string>> Validator::SfinderCover(set<string> CoverSequences, vector<string> GluedFumens) {
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
        ReturnSfinderOutput("cover -H avoid -fp \"" + FieldPath.string() + "\" -pp \"" + PatternPath.string() + "\" -d softdrop -m no -M normal -P no -o \"" + CSVFilePath.string() + "\"");
        std::ifstream CSVFileStream(CSVFilePath);
        return ReadCSV(CSVFileStream);
    }

string Validator::OverwriteFumen(string Original, string Overwrite) { //TODO
    throw std::runtime_error("Function not yet impletemented.");
    //FumenConvertObj.ConvertFumen(Original);
    //FumenConvertObj.ConvertFumen(Overwrite);
    //return RunCommand(f"node field-overwriter.js {Original} {Overwrite}"); //rewrite this in native c++
    return "";
}

vector<string> Validator::GlueFumens(vector<string> UngluedFumens) {
    fs::path FumenPath = Config.WorkingDir / "temp/unglued_fumen_temp.txt";
    std::ofstream FumenStream(FumenPath);
    for (const auto& UngluedFumen : UngluedFumens) {
        FumenStream << UngluedFumen << "\n";
    }
    FumenStream.close();
    return RunCommand("node ./dependancies/glueFumen.js --fp \"" + FumenPath.string() + "\" --s --so");
}

float Validator::SfinderPercent(std::set<int> UsedPieceIndexes, std::set<string> CoverSequences) {
    string Fumen = IndexesToFumen(UsedPieceIndexes, false);
    fs::path PatternPath = Config.WorkingDir / R"(temp/pattern_temp.txt)";
    std::ofstream PatternStream(PatternPath);
    for (const auto& coverSequence : CoverSequences) {
        PatternStream << coverSequence << "\n";
    }
    PatternStream.close();
    vector<string> SfinderOutput = ReturnSfinderOutput("percent -H use -t " + Fumen + " -P 1 -pp \"" + PatternPath.string() + "\" -c 4 -d softdrop -th -1 -td 0 -fc 0 -d 180");

    std::regex Regex(R"(success = ([\d.]+)%)");
    string Result;
    for (const auto& line : SfinderOutput) {
        std::smatch RegexMatch;
        if (std::regex_search(line, RegexMatch, Regex)) {
            Result = RegexMatch[1];
        }
    }
    if (Result != "") {
        return std::stof(Result) / 100;
    }
    else {
        throw std::runtime_error("Success percentage is not found");
    }
}

string Validator::SwapHoldHead(string Sequence) {
    return Sequence.substr(1, 1) + Sequence.substr(0, 1) + Sequence.substr(2);
}

set<string> Validator::ReturnCoveredQueues(set<int> PieceIndexes, set<string> CoverSequences) {
    set<string> OutputSequences;
    string SetupFumen = IndexesToFumen(PieceIndexes, true);

    set<string> ExpandedCoverSequences;
    for (auto const& sequence : CoverSequences) {
        ExpandedCoverSequences.insert(sequence);
        ExpandedCoverSequences.insert(SwapHoldHead(sequence));
    }

    vector<vector<string>> CoverData = SfinderCover(ExpandedCoverSequences, GlueFumens({SetupFumen}));
    CoverData.erase(CoverData.begin());

    set<string> AcceptedSequences;
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