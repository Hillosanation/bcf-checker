#include "Piece.h"

int Piece::AsIndex() const {
	return Index;
}

Piece Piece::Mirror() const {
	return { MirrorMap.at(Index) };
}

char Piece::AsTetromino() const {
    return TetrominoDict.at(Index);
}

int Piece::AsFumenIndex() const {
	return FumenIndex.at(AsTetromino());
}

bool Piece::operator==(const Piece& rhs) const {
	return this->Index == rhs.AsIndex();
}

unordered_set<int> Piece::AsMinoIndex() const {
    return FieldPermutations.at(Index);
}

const unordered_map<int, char> Piece::TetrominoDict = {
    {  0, 'I'},
    {  1, 'I'},
    {  2, 'I'},
    {  3, 'I'},
    {  4, 'I'},
    {  5, 'I'},
    {  6, 'I'},
    {  7, 'I'},
    {  8, 'I'},
    {  9, 'I'},
    { 10, 'I'},
    { 11, 'I'},
    { 12, 'I'},
    { 13, 'I'},
    { 14, 'I'},
    { 15, 'I'},
    { 16, 'I'},
    { 17, 'I'},
    { 18, 'I'},
    { 19, 'I'},
    { 20, 'I'},
    { 21, 'I'},
    { 22, 'I'},
    { 23, 'I'},
    { 24, 'I'},
    { 25, 'I'},
    { 26, 'I'},
    { 27, 'I'},
    { 28, 'I'},
    { 29, 'I'},
    { 30, 'I'},
    { 31, 'I'},
    { 32, 'I'},
    { 33, 'I'},
    { 34, 'I'},
    { 35, 'I'},
    { 36, 'I'},
    { 37, 'I'},
    { 38, 'L'},
    { 39, 'L'},
    { 40, 'L'},
    { 41, 'L'},
    { 42, 'L'},
    { 43, 'L'},
    { 44, 'L'},
    { 45, 'L'},
    { 46, 'L'},
    { 47, 'L'},
    { 48, 'L'},
    { 49, 'L'},
    { 50, 'L'},
    { 51, 'L'},
    { 52, 'L'},
    { 53, 'L'},
    { 54, 'L'},
    { 55, 'L'},
    { 56, 'L'},
    { 57, 'L'},
    { 58, 'L'},
    { 59, 'L'},
    { 60, 'L'},
    { 61, 'L'},
    { 62, 'L'},
    { 63, 'L'},
    { 64, 'L'},
    { 65, 'L'},
    { 66, 'L'},
    { 67, 'L'},
    { 68, 'L'},
    { 69, 'L'},
    { 70, 'L'},
    { 71, 'L'},
    { 72, 'L'},
    { 73, 'L'},
    { 74, 'L'},
    { 75, 'L'},
    { 76, 'L'},
    { 77, 'L'},
    { 78, 'L'},
    { 79, 'L'},
    { 80, 'L'},
    { 81, 'L'},
    { 82, 'L'},
    { 83, 'L'},
    { 84, 'L'},
    { 85, 'L'},
    { 86, 'L'},
    { 87, 'L'},
    { 88, 'L'},
    { 89, 'L'},
    { 90, 'L'},
    { 91, 'L'},
    { 92, 'L'},
    { 93, 'L'},
    { 94, 'L'},
    { 95, 'L'},
    { 96, 'L'},
    { 97, 'L'},
    { 98, 'L'},
    { 99, 'L'},
    {100, 'L'},
    {101, 'L'},
    {102, 'L'},
    {103, 'L'},
    {104, 'L'},
    {105, 'L'},
    {106, 'L'},
    {107, 'L'},
    {108, 'L'},
    {109, 'L'},
    {110, 'L'},
    {111, 'L'},
    {112, 'L'},
    {113, 'L'},
    {114, 'L'},
    {115, 'L'},
    {116, 'L'},
    {117, 'L'},
    {118, 'L'},
    {119, 'L'},
    {120, 'L'},
    {121, 'L'},
    {122, 'J'},
    {123, 'J'},
    {124, 'J'},
    {125, 'J'},
    {126, 'J'},
    {127, 'J'},
    {128, 'J'},
    {129, 'J'},
    {130, 'J'},
    {131, 'J'},
    {132, 'J'},
    {133, 'J'},
    {134, 'J'},
    {135, 'J'},
    {136, 'J'},
    {137, 'J'},
    {138, 'J'},
    {139, 'J'},
    {140, 'J'},
    {141, 'J'},
    {142, 'J'},
    {143, 'J'},
    {144, 'J'},
    {145, 'J'},
    {146, 'J'},
    {147, 'J'},
    {148, 'J'},
    {149, 'J'},
    {150, 'J'},
    {151, 'J'},
    {152, 'J'},
    {153, 'J'},
    {154, 'J'},
    {155, 'J'},
    {156, 'J'},
    {157, 'J'},
    {158, 'J'},
    {159, 'J'},
    {160, 'J'},
    {161, 'J'},
    {162, 'J'},
    {163, 'J'},
    {164, 'J'},
    {165, 'J'},
    {166, 'J'},
    {167, 'J'},
    {168, 'J'},
    {169, 'J'},
    {170, 'J'},
    {171, 'J'},
    {172, 'J'},
    {173, 'J'},
    {174, 'J'},
    {175, 'J'},
    {176, 'J'},
    {177, 'J'},
    {178, 'J'},
    {179, 'J'},
    {180, 'J'},
    {181, 'J'},
    {182, 'J'},
    {183, 'J'},
    {184, 'J'},
    {185, 'J'},
    {186, 'J'},
    {187, 'J'},
    {188, 'J'},
    {189, 'J'},
    {190, 'J'},
    {191, 'J'},
    {192, 'J'},
    {193, 'J'},
    {194, 'J'},
    {195, 'J'},
    {196, 'J'},
    {197, 'J'},
    {198, 'J'},
    {199, 'J'},
    {200, 'J'},
    {201, 'J'},
    {202, 'J'},
    {203, 'J'},
    {204, 'J'},
    {205, 'J'},
    {206, 'O'},
    {207, 'O'},
    {208, 'O'},
    {209, 'O'},
    {210, 'O'},
    {211, 'O'},
    {212, 'O'},
    {213, 'O'},
    {214, 'O'},
    {215, 'O'},
    {216, 'O'},
    {217, 'O'},
    {218, 'O'},
    {219, 'O'},
    {220, 'O'},
    {221, 'O'},
    {222, 'O'},
    {223, 'O'},
    {224, 'O'},
    {225, 'O'},
    {226, 'O'},
    {227, 'O'},
    {228, 'O'},
    {229, 'O'},
    {230, 'O'},
    {231, 'O'},
    {232, 'O'},
    {233, 'S'},
    {234, 'S'},
    {235, 'S'},
    {236, 'S'},
    {237, 'S'},
    {238, 'S'},
    {239, 'S'},
    {240, 'S'},
    {241, 'S'},
    {242, 'S'},
    {243, 'S'},
    {244, 'S'},
    {245, 'S'},
    {246, 'S'},
    {247, 'S'},
    {248, 'S'},
    {249, 'S'},
    {250, 'S'},
    {251, 'S'},
    {252, 'S'},
    {253, 'S'},
    {254, 'S'},
    {255, 'S'},
    {256, 'S'},
    {257, 'S'},
    {258, 'S'},
    {259, 'S'},
    {260, 'S'},
    {261, 'S'},
    {262, 'S'},
    {263, 'S'},
    {264, 'S'},
    {265, 'S'},
    {266, 'S'},
    {267, 'S'},
    {268, 'S'},
    {269, 'S'},
    {270, 'S'},
    {271, 'S'},
    {272, 'S'},
    {273, 'S'},
    {274, 'S'},
    {275, 'T'},
    {276, 'T'},
    {277, 'T'},
    {278, 'T'},
    {279, 'T'},
    {280, 'T'},
    {281, 'T'},
    {282, 'T'},
    {283, 'T'},
    {284, 'T'},
    {285, 'T'},
    {286, 'T'},
    {287, 'T'},
    {288, 'T'},
    {289, 'T'},
    {290, 'T'},
    {291, 'T'},
    {292, 'T'},
    {293, 'T'},
    {294, 'T'},
    {295, 'T'},
    {296, 'T'},
    {297, 'T'},
    {298, 'T'},
    {299, 'T'},
    {300, 'T'},
    {301, 'T'},
    {302, 'T'},
    {303, 'T'},
    {304, 'T'},
    {305, 'T'},
    {306, 'T'},
    {307, 'T'},
    {308, 'T'},
    {309, 'T'},
    {310, 'T'},
    {311, 'T'},
    {312, 'T'},
    {313, 'T'},
    {314, 'T'},
    {315, 'T'},
    {316, 'T'},
    {317, 'T'},
    {318, 'T'},
    {319, 'T'},
    {320, 'T'},
    {321, 'T'},
    {322, 'T'},
    {323, 'T'},
    {324, 'T'},
    {325, 'T'},
    {326, 'T'},
    {327, 'T'},
    {328, 'T'},
    {329, 'T'},
    {330, 'T'},
    {331, 'T'},
    {332, 'T'},
    {333, 'T'},
    {334, 'T'},
    {335, 'T'},
    {336, 'T'},
    {337, 'T'},
    {338, 'T'},
    {339, 'T'},
    {340, 'T'},
    {341, 'T'},
    {342, 'T'},
    {343, 'T'},
    {344, 'T'},
    {345, 'T'},
    {346, 'T'},
    {347, 'T'},
    {348, 'T'},
    {349, 'T'},
    {350, 'T'},
    {351, 'T'},
    {352, 'T'},
    {353, 'T'},
    {354, 'T'},
    {355, 'T'},
    {356, 'T'},
    {357, 'T'},
    {358, 'T'},
    {359, 'Z'},
    {360, 'Z'},
    {361, 'Z'},
    {362, 'Z'},
    {363, 'Z'},
    {364, 'Z'},
    {365, 'Z'},
    {366, 'Z'},
    {367, 'Z'},
    {368, 'Z'},
    {369, 'Z'},
    {370, 'Z'},
    {371, 'Z'},
    {372, 'Z'},
    {373, 'Z'},
    {374, 'Z'},
    {375, 'Z'},
    {376, 'Z'},
    {377, 'Z'},
    {378, 'Z'},
    {379, 'Z'},
    {380, 'Z'},
    {381, 'Z'},
    {382, 'Z'},
    {383, 'Z'},
    {384, 'Z'},
    {385, 'Z'},
    {386, 'Z'},
    {387, 'Z'},
    {388, 'Z'},
    {389, 'Z'},
    {390, 'Z'},
    {391, 'Z'},
    {392, 'Z'},
    {393, 'Z'},
    {394, 'Z'},
    {395, 'Z'},
    {396, 'Z'},
    {397, 'Z'},
    {398, 'Z'},
    {399, 'Z'},
    {400, 'Z'},
};

const unordered_map<int, int> Piece::MirrorMap = {
        {  0,  6},
        {  1,  5},
        {  2,  4},
        {  3,  3},
        {  4,  2},
        {  5,  1},
        {  6,  0},
        {  7, 13},
        {  8, 12},
        {  9, 11},
        { 10, 10},
        { 11,  9},
        { 12,  8},
        { 13,  7},
        { 14, 20},
        { 15, 19},
        { 16, 18},
        { 17, 17},
        { 18, 16},
        { 19, 15},
        { 20, 14},
        { 21, 27},
        { 22, 26},
        { 23, 25},
        { 24, 24},
        { 25, 23},
        { 26, 22},
        { 27, 21},
        { 28, 37},
        { 29, 36},
        { 30, 35},
        { 31, 34},
        { 32, 33},
        { 33, 32},
        { 34, 31},
        { 35, 30},
        { 36, 29},
        { 37, 28},
        { 38,129},
        { 39,128},
        { 40,127},
        { 41,126},
        { 42,125},
        { 43,124},
        { 44,123},
        { 45,122},
        { 46,137},
        { 47,136},
        { 48,135},
        { 49,134},
        { 50,133},
        { 51,132},
        { 52,131},
        { 53,130},
        { 54,145},
        { 55,144},
        { 56,143},
        { 57,142},
        { 58,141},
        { 59,140},
        { 60,139},
        { 61,138},
        { 62,196},
        { 63,195},
        { 64,194},
        { 65,193},
        { 66,192},
        { 67,191},
        { 68,190},
        { 69,189},
        { 70,188},
        { 71,205},
        { 72,204},
        { 73,203},
        { 74,202},
        { 75,201},
        { 76,200},
        { 77,199},
        { 78,198},
        { 79,197},
        { 80,171},
        { 81,170},
        { 82,169},
        { 83,168},
        { 84,167},
        { 85,166},
        { 86,165},
        { 87,164},
        { 88,179},
        { 89,178},
        { 90,177},
        { 91,176},
        { 92,175},
        { 93,174},
        { 94,173},
        { 95,172},
        { 96,187},
        { 97,186},
        { 98,185},
        { 99,184},
        {100,183},
        {101,182},
        {102,181},
        {103,180},
        {104,154},
        {105,153},
        {106,152},
        {107,151},
        {108,150},
        {109,149},
        {110,148},
        {111,147},
        {112,146},
        {113,163},
        {114,162},
        {115,161},
        {116,160},
        {117,159},
        {118,158},
        {119,157},
        {120,156},
        {121,155},
        {122, 45},
        {123, 44},
        {124, 43},
        {125, 42},
        {126, 41},
        {127, 40},
        {128, 39},
        {129, 38},
        {130, 53},
        {131, 52},
        {132, 51},
        {133, 50},
        {134, 49},
        {135, 48},
        {136, 47},
        {137, 46},
        {138, 61},
        {139, 60},
        {140, 59},
        {141, 58},
        {142, 57},
        {143, 56},
        {144, 55},
        {145, 54},
        {146,112},
        {147,111},
        {148,110},
        {149,109},
        {150,108},
        {151,107},
        {152,106},
        {153,105},
        {154,104},
        {155,121},
        {156,120},
        {157,119},
        {158,118},
        {159,117},
        {160,116},
        {161,115},
        {162,114},
        {163,113},
        {164, 87},
        {165, 86},
        {166, 85},
        {167, 84},
        {168, 83},
        {169, 82},
        {170, 81},
        {171, 80},
        {172, 95},
        {173, 94},
        {174, 93},
        {175, 92},
        {176, 91},
        {177, 90},
        {178, 89},
        {179, 88},
        {180,103},
        {181,102},
        {182,101},
        {183,100},
        {184, 99},
        {185, 98},
        {186, 97},
        {187, 96},
        {188, 70},
        {189, 69},
        {190, 68},
        {191, 67},
        {192, 66},
        {193, 65},
        {194, 64},
        {195, 63},
        {196, 62},
        {197, 79},
        {198, 78},
        {199, 77},
        {200, 76},
        {201, 75},
        {202, 74},
        {203, 73},
        {204, 72},
        {205, 71},
        {206,214},
        {207,213},
        {208,212},
        {209,211},
        {210,210},
        {211,209},
        {212,208},
        {213,207},
        {214,206},
        {215,223},
        {216,222},
        {217,221},
        {218,220},
        {219,219},
        {220,218},
        {221,217},
        {222,216},
        {223,215},
        {224,232},
        {225,231},
        {226,230},
        {227,229},
        {228,228},
        {229,227},
        {230,226},
        {231,225},
        {232,224},
        {233,366},
        {234,365},
        {235,364},
        {236,363},
        {237,362},
        {238,361},
        {239,360},
        {240,359},
        {241,374},
        {242,373},
        {243,372},
        {244,371},
        {245,370},
        {246,369},
        {247,368},
        {248,367},
        {249,382},
        {250,381},
        {251,380},
        {252,379},
        {253,378},
        {254,377},
        {255,376},
        {256,375},
        {257,391},
        {258,390},
        {259,389},
        {260,388},
        {261,387},
        {262,386},
        {263,385},
        {264,384},
        {265,383},
        {266,400},
        {267,399},
        {268,398},
        {269,397},
        {270,396},
        {271,395},
        {272,394},
        {273,393},
        {274,392},
        {275,282},
        {276,281},
        {277,280},
        {278,279},
        {279,278},
        {280,277},
        {281,276},
        {282,275},
        {283,290},
        {284,289},
        {285,288},
        {286,287},
        {287,286},
        {288,285},
        {289,284},
        {290,283},
        {291,298},
        {292,297},
        {293,296},
        {294,295},
        {295,294},
        {296,293},
        {297,292},
        {298,291},
        {299,349},
        {300,348},
        {301,347},
        {302,346},
        {303,345},
        {304,344},
        {305,343},
        {306,342},
        {307,341},
        {308,358},
        {309,357},
        {310,356},
        {311,355},
        {312,354},
        {313,353},
        {314,352},
        {315,351},
        {316,350},
        {317,324},
        {318,323},
        {319,322},
        {320,321},
        {321,320},
        {322,319},
        {323,318},
        {324,317},
        {325,332},
        {326,331},
        {327,330},
        {328,329},
        {329,328},
        {330,327},
        {331,326},
        {332,325},
        {333,340},
        {334,339},
        {335,338},
        {336,337},
        {337,336},
        {338,335},
        {339,334},
        {340,333},
        {341,307},
        {342,306},
        {343,305},
        {344,304},
        {345,303},
        {346,302},
        {347,301},
        {348,300},
        {349,299},
        {350,316},
        {351,315},
        {352,314},
        {353,313},
        {354,312},
        {355,311},
        {356,310},
        {357,309},
        {358,308},
        {359,240},
        {360,239},
        {361,238},
        {362,237},
        {363,236},
        {364,235},
        {365,234},
        {366,233},
        {367,248},
        {368,247},
        {369,246},
        {370,245},
        {371,244},
        {372,243},
        {373,242},
        {374,241},
        {375,256},
        {376,255},
        {377,254},
        {378,253},
        {379,252},
        {380,251},
        {381,250},
        {382,249},
        {383,265},
        {384,264},
        {385,263},
        {386,262},
        {387,261},
        {388,260},
        {389,259},
        {390,258},
        {391,257},
        {392,274},
        {393,273},
        {394,272},
        {395,271},
        {396,270},
        {397,269},
        {398,268},
        {399,267},
        {400,266},
};

const unordered_map<char, int> Piece::FumenIndex = {
        { 'I', 1 },
        { 'L', 2 },
        { 'J', 6 },
        { 'O', 3 },
        { 'S', 7 },
        { 'T', 5 },
        { 'Z', 4 },
};

const vector<unordered_set<int>> Piece::FieldPermutations = {
        {0,1,2,3,},
        {1,2,3,4,},
        {2,3,4,5,},
        {3,4,5,6,},
        {4,5,6,7,},
        {5,6,7,8,},
        {6,7,8,9,},
        {10,11,12,13,},
        {11,12,13,14,},
        {12,13,14,15,},
        {13,14,15,16,},
        {14,15,16,17,},
        {15,16,17,18,},
        {16,17,18,19,},
        {20,21,22,23,},
        {21,22,23,24,},
        {22,23,24,25,},
        {23,24,25,26,},
        {24,25,26,27,},
        {25,26,27,28,},
        {26,27,28,29,},
        {30,31,32,33,},
        {31,32,33,34,},
        {32,33,34,35,},
        {33,34,35,36,},
        {34,35,36,37,},
        {35,36,37,38,},
        {36,37,38,39,},
        {0,10,20,30,},
        {1,11,21,31,},
        {2,12,22,32,},
        {3,13,23,33,},
        {4,14,24,34,},
        {5,15,25,35,},
        {6,16,26,36,},
        {7,17,27,37,},
        {8,18,28,38,},
        {9,19,29,39,},
        {2,10,11,12,},
        {3,11,12,13,},
        {4,12,13,14,},
        {5,13,14,15,},
        {6,14,15,16,},
        {7,15,16,17,},
        {8,16,17,18,},
        {9,17,18,19,},
        {12,20,21,22,},
        {13,21,22,23,},
        {14,22,23,24,},
        {15,23,24,25,},
        {16,24,25,26,},
        {17,25,26,27,},
        {18,26,27,28,},
        {19,27,28,29,},
        {22,30,31,32,},
        {23,31,32,33,},
        {24,32,33,34,},
        {25,33,34,35,},
        {26,34,35,36,},
        {27,35,36,37,},
        {28,36,37,38,},
        {29,37,38,39,},
        {0,10,20,21,},
        {1,11,21,22,},
        {2,12,22,23,},
        {3,13,23,24,},
        {4,14,24,25,},
        {5,15,25,26,},
        {6,16,26,27,},
        {7,17,27,28,},
        {8,18,28,29,},
        {10,20,30,31,},
        {11,21,31,32,},
        {12,22,32,33,},
        {13,23,33,34,},
        {14,24,34,35,},
        {15,25,35,36,},
        {16,26,36,37,},
        {17,27,37,38,},
        {18,28,38,39,},
        {0,1,2,10,},
        {1,2,3,11,},
        {2,3,4,12,},
        {3,4,5,13,},
        {4,5,6,14,},
        {5,6,7,15,},
        {6,7,8,16,},
        {7,8,9,17,},
        {10,11,12,20,},
        {11,12,13,21,},
        {12,13,14,22,},
        {13,14,15,23,},
        {14,15,16,24,},
        {15,16,17,25,},
        {16,17,18,26,},
        {17,18,19,27,},
        {20,21,22,30,},
        {21,22,23,31,},
        {22,23,24,32,},
        {23,24,25,33,},
        {24,25,26,34,},
        {25,26,27,35,},
        {26,27,28,36,},
        {27,28,29,37,},
        {0,1,11,21,},
        {1,2,12,22,},
        {2,3,13,23,},
        {3,4,14,24,},
        {4,5,15,25,},
        {5,6,16,26,},
        {6,7,17,27,},
        {7,8,18,28,},
        {8,9,19,29,},
        {10,11,21,31,},
        {11,12,22,32,},
        {12,13,23,33,},
        {13,14,24,34,},
        {14,15,25,35,},
        {15,16,26,36,},
        {16,17,27,37,},
        {17,18,28,38,},
        {18,19,29,39,},
        {0,10,11,12,},
        {1,11,12,13,},
        {2,12,13,14,},
        {3,13,14,15,},
        {4,14,15,16,},
        {5,15,16,17,},
        {6,16,17,18,},
        {7,17,18,19,},
        {10,20,21,22,},
        {11,21,22,23,},
        {12,22,23,24,},
        {13,23,24,25,},
        {14,24,25,26,},
        {15,25,26,27,},
        {16,26,27,28,},
        {17,27,28,29,},
        {20,30,31,32,},
        {21,31,32,33,},
        {22,32,33,34,},
        {23,33,34,35,},
        {24,34,35,36,},
        {25,35,36,37,},
        {26,36,37,38,},
        {27,37,38,39,},
        {0,1,10,20,},
        {1,2,11,21,},
        {2,3,12,22,},
        {3,4,13,23,},
        {4,5,14,24,},
        {5,6,15,25,},
        {6,7,16,26,},
        {7,8,17,27,},
        {8,9,18,28,},
        {10,11,20,30,},
        {11,12,21,31,},
        {12,13,22,32,},
        {13,14,23,33,},
        {14,15,24,34,},
        {15,16,25,35,},
        {16,17,26,36,},
        {17,18,27,37,},
        {18,19,28,38,},
        {0,1,2,12,},
        {1,2,3,13,},
        {2,3,4,14,},
        {3,4,5,15,},
        {4,5,6,16,},
        {5,6,7,17,},
        {6,7,8,18,},
        {7,8,9,19,},
        {10,11,12,22,},
        {11,12,13,23,},
        {12,13,14,24,},
        {13,14,15,25,},
        {14,15,16,26,},
        {15,16,17,27,},
        {16,17,18,28,},
        {17,18,19,29,},
        {20,21,22,32,},
        {21,22,23,33,},
        {22,23,24,34,},
        {23,24,25,35,},
        {24,25,26,36,},
        {25,26,27,37,},
        {26,27,28,38,},
        {27,28,29,39,},
        {1,11,20,21,},
        {2,12,21,22,},
        {3,13,22,23,},
        {4,14,23,24,},
        {5,15,24,25,},
        {6,16,25,26,},
        {7,17,26,27,},
        {8,18,27,28,},
        {9,19,28,29,},
        {11,21,30,31,},
        {12,22,31,32,},
        {13,23,32,33,},
        {14,24,33,34,},
        {15,25,34,35,},
        {16,26,35,36,},
        {17,27,36,37,},
        {18,28,37,38,},
        {19,29,38,39,},
        {0,1,10,11,},
        {1,2,11,12,},
        {2,3,12,13,},
        {3,4,13,14,},
        {4,5,14,15,},
        {5,6,15,16,},
        {6,7,16,17,},
        {7,8,17,18,},
        {8,9,18,19,},
        {10,11,20,21,},
        {11,12,21,22,},
        {12,13,22,23,},
        {13,14,23,24,},
        {14,15,24,25,},
        {15,16,25,26,},
        {16,17,26,27,},
        {17,18,27,28,},
        {18,19,28,29,},
        {20,21,30,31,},
        {21,22,31,32,},
        {22,23,32,33,},
        {23,24,33,34,},
        {24,25,34,35,},
        {25,26,35,36,},
        {26,27,36,37,},
        {27,28,37,38,},
        {28,29,38,39,},
        {1,2,10,11,},
        {2,3,11,12,},
        {3,4,12,13,},
        {4,5,13,14,},
        {5,6,14,15,},
        {6,7,15,16,},
        {7,8,16,17,},
        {8,9,17,18,},
        {11,12,20,21,},
        {12,13,21,22,},
        {13,14,22,23,},
        {14,15,23,24,},
        {15,16,24,25,},
        {16,17,25,26,},
        {17,18,26,27,},
        {18,19,27,28,},
        {21,22,30,31,},
        {22,23,31,32,},
        {23,24,32,33,},
        {24,25,33,34,},
        {25,26,34,35,},
        {26,27,35,36,},
        {27,28,36,37,},
        {28,29,37,38,},
        {0,10,11,21,},
        {1,11,12,22,},
        {2,12,13,23,},
        {3,13,14,24,},
        {4,14,15,25,},
        {5,15,16,26,},
        {6,16,17,27,},
        {7,17,18,28,},
        {8,18,19,29,},
        {10,20,21,31,},
        {11,21,22,32,},
        {12,22,23,33,},
        {13,23,24,34,},
        {14,24,25,35,},
        {15,25,26,36,},
        {16,26,27,37,},
        {17,27,28,38,},
        {18,28,29,39,},
        {1,10,11,12,},
        {2,11,12,13,},
        {3,12,13,14,},
        {4,13,14,15,},
        {5,14,15,16,},
        {6,15,16,17,},
        {7,16,17,18,},
        {8,17,18,19,},
        {11,20,21,22,},
        {12,21,22,23,},
        {13,22,23,24,},
        {14,23,24,25,},
        {15,24,25,26,},
        {16,25,26,27,},
        {17,26,27,28,},
        {18,27,28,29,},
        {21,30,31,32,},
        {22,31,32,33,},
        {23,32,33,34,},
        {24,33,34,35,},
        {25,34,35,36,},
        {26,35,36,37,},
        {27,36,37,38,},
        {28,37,38,39,},
        {0,10,11,20,},
        {1,11,12,21,},
        {2,12,13,22,},
        {3,13,14,23,},
        {4,14,15,24,},
        {5,15,16,25,},
        {6,16,17,26,},
        {7,17,18,27,},
        {8,18,19,28,},
        {10,20,21,30,},
        {11,21,22,31,},
        {12,22,23,32,},
        {13,23,24,33,},
        {14,24,25,34,},
        {15,25,26,35,},
        {16,26,27,36,},
        {17,27,28,37,},
        {18,28,29,38,},
        {0,1,2,11,},
        {1,2,3,12,},
        {2,3,4,13,},
        {3,4,5,14,},
        {4,5,6,15,},
        {5,6,7,16,},
        {6,7,8,17,},
        {7,8,9,18,},
        {10,11,12,21,},
        {11,12,13,22,},
        {12,13,14,23,},
        {13,14,15,24,},
        {14,15,16,25,},
        {15,16,17,26,},
        {16,17,18,27,},
        {17,18,19,28,},
        {20,21,22,31,},
        {21,22,23,32,},
        {22,23,24,33,},
        {23,24,25,34,},
        {24,25,26,35,},
        {25,26,27,36,},
        {26,27,28,37,},
        {27,28,29,38,},
        {1,10,11,21,},
        {2,11,12,22,},
        {3,12,13,23,},
        {4,13,14,24,},
        {5,14,15,25,},
        {6,15,16,26,},
        {7,16,17,27,},
        {8,17,18,28,},
        {9,18,19,29,},
        {11,20,21,31,},
        {12,21,22,32,},
        {13,22,23,33,},
        {14,23,24,34,},
        {15,24,25,35,},
        {16,25,26,36,},
        {17,26,27,37,},
        {18,27,28,38,},
        {19,28,29,39,},
        {0,1,11,12,},
        {1,2,12,13,},
        {2,3,13,14,},
        {3,4,14,15,},
        {4,5,15,16,},
        {5,6,16,17,},
        {6,7,17,18,},
        {7,8,18,19,},
        {10,11,21,22,},
        {11,12,22,23,},
        {12,13,23,24,},
        {13,14,24,25,},
        {14,15,25,26,},
        {15,16,26,27,},
        {16,17,27,28,},
        {17,18,28,29,},
        {20,21,31,32,},
        {21,22,32,33,},
        {22,23,33,34,},
        {23,24,34,35,},
        {24,25,35,36,},
        {25,26,36,37,},
        {26,27,37,38,},
        {27,28,38,39,},
        {1,10,11,20,},
        {2,11,12,21,},
        {3,12,13,22,},
        {4,13,14,23,},
        {5,14,15,24,},
        {6,15,16,25,},
        {7,16,17,26,},
        {8,17,18,27,},
        {9,18,19,28,},
        {11,20,21,30,},
        {12,21,22,31,},
        {13,22,23,32,},
        {14,23,24,33,},
        {15,24,25,34,},
        {16,25,26,35,},
        {17,26,27,36,},
        {18,27,28,37,},
        {19,28,29,38,},
        {2,20,21,22,},
        {3,21,22,23,},
        {4,22,23,24,},
        {5,23,24,25,},
        {6,24,25,26,},
        {7,25,26,27,},
        {8,26,27,28,},
        {9,27,28,29,},
        {2,30,31,32,},
        {3,31,32,33,},
        {4,32,33,34,},
        {5,33,34,35,},
        {6,34,35,36,},
        {7,35,36,37,},
        {8,36,37,38,},
        {9,37,38,39,},
        {12,30,31,32,},
        {13,31,32,33,},
        {14,32,33,34,},
        {15,33,34,35,},
        {16,34,35,36,},
        {17,35,36,37,},
        {18,36,37,38,},
        {19,37,38,39,},
        {0,20,30,31,},
        {1,21,31,32,},
        {2,22,32,33,},
        {3,23,33,34,},
        {4,24,34,35,},
        {5,25,35,36,},
        {6,26,36,37,},
        {7,27,37,38,},
        {8,28,38,39,},
        {0,10,30,31,},
        {1,11,31,32,},
        {2,12,32,33,},
        {3,13,33,34,},
        {4,14,34,35,},
        {5,15,35,36,},
        {6,16,36,37,},
        {7,17,37,38,},
        {8,18,38,39,},
        {0,1,2,20,},
        {1,2,3,21,},
        {2,3,4,22,},
        {3,4,5,23,},
        {4,5,6,24,},
        {5,6,7,25,},
        {6,7,8,26,},
        {7,8,9,27,},
        {0,1,2,30,},
        {1,2,3,31,},
        {2,3,4,32,},
        {3,4,5,33,},
        {4,5,6,34,},
        {5,6,7,35,},
        {6,7,8,36,},
        {7,8,9,37,},
        {10,11,12,30,},
        {11,12,13,31,},
        {12,13,14,32,},
        {13,14,15,33,},
        {14,15,16,34,},
        {15,16,17,35,},
        {16,17,18,36,},
        {17,18,19,37,},
        {0,1,21,31,},
        {1,2,22,32,},
        {2,3,23,33,},
        {3,4,24,34,},
        {4,5,25,35,},
        {5,6,26,36,},
        {6,7,27,37,},
        {7,8,28,38,},
        {8,9,29,39,},
        {0,1,11,31,},
        {1,2,12,32,},
        {2,3,13,33,},
        {3,4,14,34,},
        {4,5,15,35,},
        {5,6,16,36,},
        {6,7,17,37,},
        {7,8,18,38,},
        {8,9,19,39,},
        {0,20,21,22,},
        {1,21,22,23,},
        {2,22,23,24,},
        {3,23,24,25,},
        {4,24,25,26,},
        {5,25,26,27,},
        {6,26,27,28,},
        {7,27,28,29,},
        {0,30,31,32,},
        {1,31,32,33,},
        {2,32,33,34,},
        {3,33,34,35,},
        {4,34,35,36,},
        {5,35,36,37,},
        {6,36,37,38,},
        {7,37,38,39,},
        {10,30,31,32,},
        {11,31,32,33,},
        {12,32,33,34,},
        {13,33,34,35,},
        {14,34,35,36,},
        {15,35,36,37,},
        {16,36,37,38,},
        {17,37,38,39,},
        {0,1,20,30,},
        {1,2,21,31,},
        {2,3,22,32,},
        {3,4,23,33,},
        {4,5,24,34,},
        {5,6,25,35,},
        {6,7,26,36,},
        {7,8,27,37,},
        {8,9,28,38,},
        {0,1,10,30,},
        {1,2,11,31,},
        {2,3,12,32,},
        {3,4,13,33,},
        {4,5,14,34,},
        {5,6,15,35,},
        {6,7,16,36,},
        {7,8,17,37,},
        {8,9,18,38,},
        {0,1,2,22,},
        {1,2,3,23,},
        {2,3,4,24,},
        {3,4,5,25,},
        {4,5,6,26,},
        {5,6,7,27,},
        {6,7,8,28,},
        {7,8,9,29,},
        {0,1,2,32,},
        {1,2,3,33,},
        {2,3,4,34,},
        {3,4,5,35,},
        {4,5,6,36,},
        {5,6,7,37,},
        {6,7,8,38,},
        {7,8,9,39,},
        {10,11,12,32,},
        {11,12,13,33,},
        {12,13,14,34,},
        {13,14,15,35,},
        {14,15,16,36,},
        {15,16,17,37,},
        {16,17,18,38,},
        {17,18,19,39,},
        {1,21,30,31,},
        {2,22,31,32,},
        {3,23,32,33,},
        {4,24,33,34,},
        {5,25,34,35,},
        {6,26,35,36,},
        {7,27,36,37,},
        {8,28,37,38,},
        {9,29,38,39,},
        {1,11,30,31,},
        {2,12,31,32,},
        {3,13,32,33,},
        {4,14,33,34,},
        {5,15,34,35,},
        {6,16,35,36,},
        {7,17,36,37,},
        {8,18,37,38,},
        {9,19,38,39,},
        {0,1,20,21,},
        {1,2,21,22,},
        {2,3,22,23,},
        {3,4,23,24,},
        {4,5,24,25,},
        {5,6,25,26,},
        {6,7,26,27,},
        {7,8,27,28,},
        {8,9,28,29,},
        {0,1,30,31,},
        {1,2,31,32,},
        {2,3,32,33,},
        {3,4,33,34,},
        {4,5,34,35,},
        {5,6,35,36,},
        {6,7,36,37,},
        {7,8,37,38,},
        {8,9,38,39,},
        {10,11,30,31,},
        {11,12,31,32,},
        {12,13,32,33,},
        {13,14,33,34,},
        {14,15,34,35,},
        {15,16,35,36,},
        {16,17,36,37,},
        {17,18,37,38,},
        {18,19,38,39,},
        {1,2,20,21,},
        {2,3,21,22,},
        {3,4,22,23,},
        {4,5,23,24,},
        {5,6,24,25,},
        {6,7,25,26,},
        {7,8,26,27,},
        {8,9,27,28,},
        {1,2,30,31,},
        {2,3,31,32,},
        {3,4,32,33,},
        {4,5,33,34,},
        {5,6,34,35,},
        {6,7,35,36,},
        {7,8,36,37,},
        {8,9,37,38,},
        {11,12,30,31,},
        {12,13,31,32,},
        {13,14,32,33,},
        {14,15,33,34,},
        {15,16,34,35,},
        {16,17,35,36,},
        {17,18,36,37,},
        {18,19,37,38,},
        {0,20,21,31,},
        {1,21,22,32,},
        {2,22,23,33,},
        {3,23,24,34,},
        {4,24,25,35,},
        {5,25,26,36,},
        {6,26,27,37,},
        {7,27,28,38,},
        {8,28,29,39,},
        {0,10,11,31,},
        {1,11,12,32,},
        {2,12,13,33,},
        {3,13,14,34,},
        {4,14,15,35,},
        {5,15,16,36,},
        {6,16,17,37,},
        {7,17,18,38,},
        {8,18,19,39,},
        {1,20,21,22,},
        {2,21,22,23,},
        {3,22,23,24,},
        {4,23,24,25,},
        {5,24,25,26,},
        {6,25,26,27,},
        {7,26,27,28,},
        {8,27,28,29,},
        {1,30,31,32,},
        {2,31,32,33,},
        {3,32,33,34,},
        {4,33,34,35,},
        {5,34,35,36,},
        {6,35,36,37,},
        {7,36,37,38,},
        {8,37,38,39,},
        {11,30,31,32,},
        {12,31,32,33,},
        {13,32,33,34,},
        {14,33,34,35,},
        {15,34,35,36,},
        {16,35,36,37,},
        {17,36,37,38,},
        {18,37,38,39,},
        {0,20,21,30,},
        {1,21,22,31,},
        {2,22,23,32,},
        {3,23,24,33,},
        {4,24,25,34,},
        {5,25,26,35,},
        {6,26,27,36,},
        {7,27,28,37,},
        {8,28,29,38,},
        {0,10,11,30,},
        {1,11,12,31,},
        {2,12,13,32,},
        {3,13,14,33,},
        {4,14,15,34,},
        {5,15,16,35,},
        {6,16,17,36,},
        {7,17,18,37,},
        {8,18,19,38,},
        {0,1,2,21,},
        {1,2,3,22,},
        {2,3,4,23,},
        {3,4,5,24,},
        {4,5,6,25,},
        {5,6,7,26,},
        {6,7,8,27,},
        {7,8,9,28,},
        {0,1,2,31,},
        {1,2,3,32,},
        {2,3,4,33,},
        {3,4,5,34,},
        {4,5,6,35,},
        {5,6,7,36,},
        {6,7,8,37,},
        {7,8,9,38,},
        {10,11,12,31,},
        {11,12,13,32,},
        {12,13,14,33,},
        {13,14,15,34,},
        {14,15,16,35,},
        {15,16,17,36,},
        {16,17,18,37,},
        {17,18,19,38,},
        {1,20,21,31,},
        {2,21,22,32,},
        {3,22,23,33,},
        {4,23,24,34,},
        {5,24,25,35,},
        {6,25,26,36,},
        {7,26,27,37,},
        {8,27,28,38,},
        {9,28,29,39,},
        {1,10,11,31,},
        {2,11,12,32,},
        {3,12,13,33,},
        {4,13,14,34,},
        {5,14,15,35,},
        {6,15,16,36,},
        {7,16,17,37,},
        {8,17,18,38,},
        {9,18,19,39,},
        {0,1,21,22,},
        {1,2,22,23,},
        {2,3,23,24,},
        {3,4,24,25,},
        {4,5,25,26,},
        {5,6,26,27,},
        {6,7,27,28,},
        {7,8,28,29,},
        {0,1,31,32,},
        {1,2,32,33,},
        {2,3,33,34,},
        {3,4,34,35,},
        {4,5,35,36,},
        {5,6,36,37,},
        {6,7,37,38,},
        {7,8,38,39,},
        {10,11,31,32,},
        {11,12,32,33,},
        {12,13,33,34,},
        {13,14,34,35,},
        {14,15,35,36,},
        {15,16,36,37,},
        {16,17,37,38,},
        {17,18,38,39,},
        {1,20,21,30,},
        {2,21,22,31,},
        {3,22,23,32,},
        {4,23,24,33,},
        {5,24,25,34,},
        {6,25,26,35,},
        {7,26,27,36,},
        {8,27,28,37,},
        {9,28,29,38,},
        {1,10,11,30,},
        {2,11,12,31,},
        {3,12,13,32,},
        {4,13,14,33,},
        {5,14,15,34,},
        {6,15,16,35,},
        {7,16,17,36,},
        {8,17,18,37,},
        {9,18,19,38,},
};