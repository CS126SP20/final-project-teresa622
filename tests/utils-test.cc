//
// Created by Teresa Dong on 5/2/20.
//

#include <catch2/catch.hpp>

#include "mylibrary/utils.h"

TEST_CASE("Generates random number within range") {
  size_t rand_num = utils::RandNumInRange(5);

  REQUIRE(rand_num >= 0);
  REQUIRE(rand_num < 5);
}