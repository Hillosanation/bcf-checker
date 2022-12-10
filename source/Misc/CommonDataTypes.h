#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include <map>
#include <fstream>
using std::string;
using std::vector;
using std::map;
using std::unordered_set;

typedef std::vector<int> PlayField;

unordered_set<int> Range(int a, int b);

const map<char, unordered_set<int>> PieceIndexesWithTetromino = {
    { 'I', Range(0,37 + 1) },
    { 'L', Range(38, 121 + 1) },
    { 'J', Range(122,205 + 1) },
    { 'O', Range(206,232 + 1) },
    { 'S', Range(233,274 + 1) },
    { 'T', Range(275,358 + 1) },
    { 'Z', Range(359,400 + 1) },
};

vector<vector<string>> ReadCSV(std::ifstream& FileStream);