// Dr. Rykalova
// test.cpp for PS1a
// updated 1/31/2020

#include <iostream>
#include <string>

#include "FibLFSR.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(sixteenBitsThreeTaps) {

  FibLFSR l("1011011000110110");
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 1);
  BOOST_REQUIRE(l.step() == 1);
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 1);

}

BOOST_AUTO_TEST_CASE(custom1) {

    FibLFSR l2("0000000000000000");

    for (int i = 0; i < 5 ; i++)
        BOOST_REQUIRE(l2.generate(i) == 0);

    FibLFSR l3("1111111111111111");
    for (int i = 0; i < 5; i++)
        BOOST_REQUIRE(l3.generate(i) == 0);

}

BOOST_AUTO_TEST_CASE(custom2) {

    FibLFSR l4("1011011000110110");
    BOOST_REQUIRE(l4.generate(9) == 51);

    FibLFSR l5("1011011000110110");
    BOOST_REQUIRE(l5.generate(5) == 3);
}