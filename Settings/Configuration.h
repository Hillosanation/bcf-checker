#pragma once
#include <set>
#include <map>
#include <string>
#include <stdexcept>
#include <filesystem>
#include <vector>
#include <any>
#include "../PercentageRecord.h"
#include "../dependancies/argparse-2.6/include/argparse/argparse.hpp"
using std::set;
using std::map;
using std::string;
using std::vector;

class Configuration { //TODO: global singleton?
	argparse::ArgumentParser parser;

public:
	const std::filesystem::path WorkingDir = std::filesystem::current_path();

	Configuration(PercentageRecord& extPercentageRecordObj, int argc, char* argv[]);

	//template<typename T> //im dumb and bad
	//T GetValue(string key) {
	//	auto x = parser.get<string>(key);
	//	return static_cast<T>((string)x);
	//}

	int GetValueInt(string key);
	double GetValueDouble(string key);
	bool GetValueBool(string key);
	string GetValueString(string key);


};
