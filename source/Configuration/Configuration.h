#pragma once
#include <string>
#include <stdexcept>
#include <filesystem>
#include <vector>
#include "../Validation/PercentageRecord.h"
#include "../dependancies/argparse-2.6/include/argparse/argparse.hpp"
using std::string;
using std::vector;

class Configuration { 
	argparse::ArgumentParser parser;

public:
	const std::filesystem::path WorkingDir = std::filesystem::current_path();

	Configuration(PercentageRecord& extPercentageRecordObj, int argc, char* argv[]);

	template<typename T> //im dumb and bad
	T GetValue(string key) const {
		return parser.get<T>(key);
	}
};
