#pragma once
#include <unordered_set>
#include <map>
#include <vector>
#include ".\Piece.h"
#include ".\Misc\CommonDataTypes.h"
using std::unordered_set;
using std::map;
using std::vector;

class Field //Handles all representations of a field
{
	const unordered_set<Piece> Pieces;

    static constexpr vector<vector<int>> FieldPermutations = {
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

public:
	Field(unordered_set<Piece> extPieces) : Pieces(extPieces) {};

    unordered_set<Piece> AsPieces() const;

    Field Mirror() const;

    PlayField AsPlayField(bool Colored = false) const;

    std::string AsFumen(bool Colored = false) const;

    bool operator==(Field& rhs) const;
	
};

