#include <iostream>
#include <string>
#include <algorithm>
#include "doctest.h"
#include "Notebook.hpp"
#include "Direction.hpp"

using namespace ariel;
using namespace std;

TEST_CASE("Throwing Exceptions")
{
    Notebook nbk;


    CHECK_THROWS(nbk.write(0, 0, 60, Direction::Horizontal, "This is a string containing more than 40 characters"));
    CHECK_THROWS(nbk.read(0, 0, 60, Direction::Horizontal, 50)); //reading out of bounds of line (more than 100 characters)
    CHECK_THROWS(nbk.erase(0, 0, 50, Direction::Horizontal, 60)); //erasing out of bounds of line (more than 100 characters)

    //for read
    CHECK_THROWS(nbk.read(-10, 0, 50, Direction::Horizontal, 10)); //negative page number
    CHECK_THROWS(nbk.read(0, -10, 50, Direction::Horizontal, 10)); //negative row number
    CHECK_THROWS(nbk.read(0, 0, -50, Direction::Horizontal, 10)); //negative column number
    CHECK_THROWS(nbk.read(0, 0, 50, Direction::Horizontal, -10)); //negative length
    CHECK_THROWS(nbk.read(-10, -10, -50, Direction::Horizontal, -10)); //every number negative
    CHECK_THROWS(nbk.read(0, 0, 0, Direction::Horizontal, 150)); //reading more thatn 100 characters

    //for erase
    CHECK_THROWS(nbk.erase(-10, 0, 50, Direction::Horizontal, 10)); //negative page number
    CHECK_THROWS(nbk.erase(0, -10, 50, Direction::Horizontal, 10)); //negative row number
    CHECK_THROWS(nbk.erase(0, 0, -50, Direction::Horizontal, 10)); //negative column number
    CHECK_THROWS(nbk.erase(0, 0, 50, Direction::Horizontal, -10)); //negative length
    CHECK_THROWS(nbk.erase(-10, -10, -50, Direction::Horizontal, -10)); //every number negative
    CHECK_THROWS(nbk.erase(0, 0, 0, Direction::Horizontal, 150)); //erasing more thatn 100 characters

    //for write
    CHECK_THROWS(nbk.write(-10, 0, 50, Direction::Horizontal, "abc")); //negative page number
    CHECK_THROWS(nbk.write(0, -10, 50, Direction::Horizontal, "abc")); //negative row number
    CHECK_THROWS(nbk.write(0, 0, -50, Direction::Horizontal, "abc")); //negative column number
    CHECK_THROWS(nbk.write(-10, -10, -50, Direction::Horizontal, "abc")); //every number negative
    CHECK_THROWS(nbk.write(0, 0, 0, Direction::Horizontal, "------------------------------------------------------------------------------------------------------------------------")); //writing more than 100 characters (120)


    nbk.write(0, 0, 0, Direction::Horizontal, "abc");
    CHECK_THROWS(nbk.write(0, 0, 0, Direction::Horizontal, "abc")); //writing a second time in the same place
    CHECK_THROWS(nbk.write(0, 0, 1, Direction::Horizontal, "abc")); //writing a second time in the same place not where we first started (partially empty space)
    CHECK_THROWS(nbk.write(0, 0, 2, Direction::Horizontal, "abc")); //writing a second time in the same place not where we first started (partially empty space)

    nbk.erase(0, 0, 0, Direction::Horizontal, 3);
    CHECK_THROWS(nbk.write(0, 0, 0, Direction::Horizontal, "abc")); //writing a second time in the same place (erased)
    CHECK_THROWS(nbk.write(0, 0, 1, Direction::Horizontal, "abc")); //same as line 46 after erase
    CHECK_THROWS(nbk.write(0, 0, 2, Direction::Horizontal, "abc")); //same as line 47 after erase

    CHECK_THROWS(nbk.write(0, 0, 0, Direction::Horizontal, "~~~")); //invalid symbol to write
}

TEST_CASE("Valid Arguments")
{
    Notebook nbk;

    nbk.write(0, 0, 0, Direction::Horizontal, "abc");
    CHECK(nbk.read(0, 0, 0, Direction::Horizontal, 3) == "abc"); //write/read to test the functions
    nbk.erase(0, 0, 0, Direction::Horizontal, 3);
    CHECK(nbk.read(0, 0, 0, Direction::Horizontal, 3) == "~~~");

    nbk.write(0, 0, 0, Direction::Vertical, "abc");
    CHECK(nbk.read(0, 0, 0, Direction::Vertical, 3) == "abc"); //write/read to test the functions on vertical
    nbk.erase(0, 0, 0, Direction::Vertical, 3);
    CHECK(nbk.read(0, 0, 0, Direction::Vertical, 3) == "~~~");

    nbk.write(1, 0, 0, Direction::Horizontal, "abc");
    CHECK(nbk.read(1, 0, 0, Direction::Horizontal, 3) == "abc"); //write/read to test the functions on different page
    nbk.erase(1, 0, 0, Direction::Horizontal, 3);
    CHECK(nbk.read(1, 0, 0, Direction::Horizontal, 3) == "~~~");

    nbk.write(0, 5, 10, Direction::Horizontal, "abc");
    CHECK(nbk.read(0, 5, 10, Direction::Horizontal, 3) == "abc"); //write/read to test the functions on places other than 0,0,0
    CHECK(nbk.read(0, 5, 20, Direction::Horizontal, 3) != "abc");
    nbk.erase(0, 5, 10, Direction::Horizontal, 3);
    CHECK(nbk.read(0, 5, 10, Direction::Horizontal, 3) == "~~~");

    CHECK(nbk.read(0, 0, 0, Direction::Horizontal, 3) == "~~~"); //check previous putput hasnt changed
}