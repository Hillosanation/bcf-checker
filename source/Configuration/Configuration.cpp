#include <fstream>
#include "./Configuration.h"
#include "../Misc/CommonDataTypes.h"

Configuration::Configuration(PercentageRecord& extPercentageRecordObj, int argc, char* argv[]) {
	parser.add_argument("-vis", "--visible-pieces")
		.required()
		.scan<'d', int>(); //combine setup&same?
	//remaining pieces are "blind", you have to conform to the constraints
	parser.add_argument("-inc", "--increased-vision")
		.default_value(1)
		.scan<'d', int>().
		help("Usually set to 1, as you see 1 new piece from the next bag for each piece you place.");
	parser.add_argument("-pp", "--placed-pieces")
		.required()
		.scan<'d', int>()
		.help("The number of pieces placed.");
	parser.add_argument("-tsp", "--tree-succeed-percentage")
		.default_value(0.001)
		.scan<'g', double>()
		.help("Include current tree if it contains at least this percentage of maximum child nodes");

	parser.add_argument("-sfp", "--sfinder-path")
		.required();
	parser.add_argument("-sp", "--sequence-path")
		.default_value((string)"input/sequence.txt");
	parser.add_argument("-op", "--output-path")
		.required();
	parser.add_argument("-sm", "--skip-mirror")
		.default_value(true)
		.help("Does not check mirror setups, only useful when exact mirrors can be built");

	try {
		parser.parse_args(argc, argv);
	}
	catch (const std::runtime_error& err) {
		std::cerr << err.what() << std::endl;
		std::cerr << parser;
		std::exit(1);
	}

	std::ifstream BestPercentageStream(WorkingDir / "input/Best_Percentages.txt");
	for (const auto& entry : ReadCSV(BestPercentageStream)) {
		extPercentageRecordObj.UpdatePercentage(entry[0], std::stod(entry[1]));
	}

}