//
// Created by Teresa Dong on 5/6/20.
//
#include <catch2/catch.hpp>

#include "mylibrary/location.h"

TEST_CASE("Equality Operator: Equal Locations") {
  tetris::Location location_one(1, 1);
  tetris::Location location_two(1,1);

  //The two locations should be equal
  REQUIRE(location_one == location_two);
}

TEST_CASE("Equality Operator: Not Equal Locations") {
  tetris::Location location_one(1, 1);
  tetris::Location location_two(1,2);

  //The two locations should not be equal
  REQUIRE(!(location_one == location_two));
}