// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "mylibrary/tetromino.h"
#include "mylibrary/tetromino_type.h"


TEST_CASE("Tetromino I") {
  mylibrary::Tetromino tetromino
  (5, mylibrary::TetrominoType::kI);

  SECTION("Initializing I") {
    mylibrary::Location pixels[4] = {mylibrary::Location(5, 0),
                                     mylibrary::Location (5, 1),
                                     mylibrary::Location(5, 2),
                                     mylibrary::Location(5, 3)};
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }

  SECTION("Move Tetromino: positive values") {
    tetromino.MoveTetromino(3, 1);
    REQUIRE(tetromino.GetPixelLocation(0) == mylibrary::Location(8, 1));
  }

  SECTION("Move Tetromino: negative horizontal values") {
    tetromino.MoveTetromino(-3, 0);
    REQUIRE(tetromino.GetPixelLocation(3) == mylibrary::Location(2, 3));
  }

  SECTION("Get Contact Pixels") {
    //The contact pixel should be the last one since it's an I
    std::vector<int> contact_indexes = tetromino.FindContactPixels();
    REQUIRE(std::find(contact_indexes.begin(), contact_indexes.end(), 3)
    != contact_indexes.end());
  }
}

TEST_CASE("Tetromino J") {
  mylibrary::Tetromino tetromino
      (5, mylibrary::TetrominoType::kJ);

  SECTION("Initializing J") {
    mylibrary::Location pixels[4] = {mylibrary::Location(5, 0),
                                     mylibrary::Location (5, 1),
                                     mylibrary::Location(5, 2),
                                     mylibrary::Location(4, 2)};
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }

  SECTION("Get Tetromino Type") {
    REQUIRE(tetromino.GetTetrominoType() == mylibrary::TetrominoType::kJ);
  }

  SECTION("Get Contact Pixels") {
    //The contact pixel should be the last two, the hook and the bottom of J
    std::vector<int> contact_indexes = tetromino.FindContactPixels();
    for (int i = 2; i < 4; i++) {
      REQUIRE(std::find(contact_indexes.begin(), contact_indexes.end(), i)
                  != contact_indexes.end());
    }
  }
}

TEST_CASE("Tetromino L") {
  mylibrary::Tetromino tetromino
      (5, mylibrary::TetrominoType::kL);

  SECTION("Initializing L") {
    mylibrary::Location pixels[4] = {mylibrary::Location(5, 0),
                                     mylibrary::Location (5, 1),
                                     mylibrary::Location(5, 2),
                                     mylibrary::Location(6, 2)};
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }

  SECTION("Get Contact Pixels") {
    //The contact pixel should be the last two, the hook and the bottom of L
    std::vector<int> contact_indexes = tetromino.FindContactPixels();
    for (int i = 2; i < 4; i++) {
      REQUIRE(std::find(contact_indexes.begin(), contact_indexes.end(), i)
                  != contact_indexes.end());
    }
  }
}

TEST_CASE("Tetromino O") {
  mylibrary::Tetromino tetromino
      (5, mylibrary::TetrominoType::kO);

  SECTION("Initializing O") {
    mylibrary::Location pixels[4] = {mylibrary::Location(4, 0),
                                     mylibrary::Location (5, 0),
                                     mylibrary::Location(4, 1),
                                     mylibrary::Location(5, 1)};
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }

  SECTION("Get Contact Pixels") {
    //The contact pixel should be the last two, the bottom of the square
    std::vector<int> contact_indexes = tetromino.FindContactPixels();
    for (int i = 2; i < 4; i++) {
      REQUIRE(std::find(contact_indexes.begin(), contact_indexes.end(), i)
                  != contact_indexes.end());
    }

    //The contact pixels should not change since O does not change
    //when rotated
    tetromino.RotateTetromino();
    contact_indexes = tetromino.FindContactPixels();
    REQUIRE(std::find(contact_indexes.begin(), contact_indexes.end(), 3)
                  != contact_indexes.end());
    REQUIRE(std::find(contact_indexes.begin(), contact_indexes.end(), 2)
                != contact_indexes.end());
  }
}

TEST_CASE("Tetromino T") {
  mylibrary::Tetromino tetromino
      (5, mylibrary::TetrominoType::kT);

  SECTION("Initializing T") {
    mylibrary::Location pixels[4] = {mylibrary::Location(4, 0),
                                     mylibrary::Location (5, 0),
                                     mylibrary::Location(6, 0),
                                     mylibrary::Location(5, 1)};
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }

  SECTION("Rotate Tetromino") {
    tetromino.RotateTetromino();
    mylibrary::Location pixels[4] = {mylibrary::Location(5, -1),
                                     mylibrary::Location (5, 0),
                                     mylibrary::Location(5, 1),
                                     mylibrary::Location(4, 0)};
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }

  SECTION("Get Contact Pixels") {
    //The original state of T has it so that it has 3 contact pixels
    std::vector<int> contact_indexes = tetromino.FindContactPixels();
    REQUIRE(contact_indexes.size() == 3);

    //After rotating, T should now only have 3 contact pixels
    tetromino.RotateTetromino();
    contact_indexes = tetromino.FindContactPixels();
    REQUIRE(contact_indexes.size() == 2);
  }
}