  #include <iostream>
#include <string>

#include "CircularBuffer.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(Check_Bad_Parameter_Constructor) {
    BOOST_CHECK_THROW(CircularBuffer(-2), invalid_argument);
}

BOOST_AUTO_TEST_CASE(Check_Size_Empty) {
    CircularBuffer circlebuf(5);
    BOOST_REQUIRE(circlebuf.isEmpty() == true);
    BOOST_REQUIRE(circlebuf.getCurrSize() == 0);
}

BOOST_AUTO_TEST_CASE(Check_Enqueue_Dequeue) {
    CircularBuffer circlebuf(2);
    circlebuf.enqueue(21);
    BOOST_REQUIRE(circlebuf.peek() == 21);
    BOOST_REQUIRE(circlebuf.dequeue() == 21);
    circlebuf.enqueue(12);
    BOOST_REQUIRE(circlebuf.peek() == 12);
}

BOOST_AUTO_TEST_CASE(Check_Enqueue_Full) {
    CircularBuffer circlebuf(2);
    circlebuf.enqueue(21);
    circlebuf.enqueue(12);
    BOOST_REQUIRE(circlebuf.isFull() == true);
    BOOST_CHECK_THROW(circlebuf.enqueue(1), runtime_error);
}

BOOST_AUTO_TEST_CASE(Check_Dequeue_Empty) {
    CircularBuffer circlebuf(0);
    BOOST_REQUIRE(circlebuf.isEmpty() == true);
    BOOST_CHECK_THROW(circlebuf.dequeue(), runtime_error);
}

BOOST_AUTO_TEST_CASE(Check_Dequeue_From_Full) {
    CircularBuffer circlebuf(2);
    circlebuf.enqueue(21);
    circlebuf.enqueue(12);
    BOOST_REQUIRE(circlebuf.isFull() == true);
    circlebuf.dequeue();
    circlebuf.dequeue();
    BOOST_REQUIRE(circlebuf.isEmpty() == true);
    BOOST_CHECK_THROW(circlebuf.dequeue(), runtime_error);
}