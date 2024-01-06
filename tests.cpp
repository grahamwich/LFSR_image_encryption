#include <iostream>
#include <string>

#include "LFSR.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>
using boost::test_tools::output_test_stream;

BOOST_AUTO_TEST_CASE(teststepinstr2) {
	LFSR l2("1011011000110110");
	BOOST_REQUIRE_EQUAL(l2.generate(9), 51);
}

BOOST_AUTO_TEST_CASE(testmultiplegenerate) {
	LFSR l3("1011011000110110");
	for(int i = 0; i < 7; i++) {
		l3.generate(5);
	}
	BOOST_REQUIRE_EQUAL(l3.getCurrSeed(), "0000010110111100");
}

BOOST_AUTO_TEST_CASE(testoutput) {
	LFSR l4("1011011000110110");
	output_test_stream output;
	output << l4;
	
	BOOST_CHECK(!output.is_empty(false));
	BOOST_TEST( output.is_equal("current seed: 1011011000110110\n" ));
}

