#include <iostream>
#include <string>
#include "LFSR.hpp"
using namespace std;

LFSR::LFSR(string seed) {
	_seed = seed;
}

int LFSR::step() {
	// 15 xor 13 -> result1, 
	// result1 xor 12 -> result2, 
	// result2 xor 10 -> result3, 
	// return 0 or 1
	int result1 = _seed[_size - (_tap1 + 1)] ^ _seed[_size - (_tap2 + 1)]; //xor 15 and 13 should be index [0] and [2] = [16-16] and [16-14] = [16 - (15+1)] and [16 - (13+1)]
	int result2 = result1 ^ _seed[_size - (_tap3 + 1)];
	int result3 = result2 ^ _seed[_size - (_tap4 + 1)];
	_tapResult = result3;

	//shift the seed 
	_seed = _seed.substr(1, 15) + to_string(result3);

	return result3;
}

int LFSR::generate(int k) {

	//initialize a variable to zeroand for each bit extracted, double the variable and add the bit returned by step().
	int result = 0;
	int kbit = 0;
	for (int i = 0; i < k; i++) {
		result = step();
		kbit = kbit * 2 + result;
	}

	//cout << _seed << " " << " kbit: " << kbit << endl;
	_kbit = kbit;

	return kbit;
}

ostream& operator<<(ostream& outStream, const LFSR& lfsr) {
	outStream << "current seed: " << lfsr._seed << endl;
			//   << "current tap result: " << lfsr._tapResult << endl 
			//   << "current kbit: " << lfsr._kbit << endl;
	return outStream;
}

string LFSR::getCurrSeed() {
	return _seed;
}

