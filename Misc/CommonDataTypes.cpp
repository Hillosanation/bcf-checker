#include "./CommonDataTypes.h"
#include <stdexcept>
#include <fstream>
#include <sstream>

set<int> Range(int a, int b) {
    set<int> OutputSet;
    for (size_t i = a; i < b; i++) {
        OutputSet.insert((int)i);
    }
    return OutputSet;
}

vector<vector<string>> ReadCSV(std::ifstream& FileStream) {
    vector<vector<string>> CSVOutput;
    string line;
    while (std::getline(FileStream, line)) {
        string item;
        vector<string> CSVRow;
        std::stringstream lineStream(line);
        while (std::getline(lineStream, item, ',')) {
            CSVRow.push_back(item);
        }
        CSVOutput.push_back(CSVRow);
    }
    return CSVOutput;
}
