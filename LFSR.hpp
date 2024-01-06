#pragma once
#include <iostream>
#include <string>

class LFSR {
public:
	// Constructor to create LFSR with the given initial seed
	LFSR(std::string seed);
	// Simulate one step and return the new bit as 0 or 1
	int step();
	// Simulate k steps and return a k-bit integer
	int generate(int k);
	friend std::ostream& operator<<(std::ostream& outStream, const LFSR& lfsr);
	
	std::string getCurrSeed(); //accessor used in boost testing
private:
	std::string _seed = "000000000000001";
	int _tapResult = 0;
	int _kbit = 0;

	//need for location (index) of taps
	const int _size = 16;
	const int _tap1 = 15;
	const int _tap2 = 13;
	const int _tap3 = 12;
	const int _tap4 = 10;
};
std::ostream& operator<<(std::ostream&, const LFSR& lfsr);


