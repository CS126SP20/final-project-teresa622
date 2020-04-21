// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "mylibrary/tetromino.h"
#include "mylibrary/tetromino_type.h"


TEST_CASE("Tetromino I") {
  mylibrary::Tetromino tetromino
  (5, mylibrary::TetrominoType::kI);

  SECTION("Initializing I") {
    mylibrary::Location pixels[4] = {mylibrary::Location(3, 1),
                                     mylibrary::Location (4, 1),
                                     mylibrary::Location(5, 1),
                                     mylibrary::Location(6, 1)};
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }

  //Tests Move Tetromino here
  SECTION("Move Tetromino: positive values") {
    tetromino.MoveTetromino(3, 1);
    REQUIRE(tetromino.GetPixelLocation(0) == mylibrary::Location(6, 2));
  }

  SECTION("Move Tetromino: negative values") {
    tetromino.MoveTetromino(-3, -1);
    REQUIRE(tetromino.GetPixelLocation(0) == mylibrary::Location(0, 0));
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
}

TEST_CASE("Tetromino T") {
  mylibrary::Tetromino tetromino
      (5, mylibrary::TetrominoType::kT);

  SECTION("Initializing T") {
    mylibrary::Location pixels[4] = {mylibrary::Location(4, 1),
                                     mylibrary::Location (5, 1),
                                     mylibrary::Location(6, 1),
                                     mylibrary::Location(5, 0)};
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }

  //Rotation of Tetromino tested here
  SECTION("Rotate Tetromino") {
    tetromino.RotateTetromino();
    mylibrary::Location pixels[4] = {mylibrary::Location(5, 0),
                                     mylibrary::Location (5, 1),
                                     mylibrary::Location(5, 2),
                                     mylibrary::Location(6, 1)};
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }
}

TEST_CASE("Tetromino S") {
  mylibrary::Tetromino tetromino
      (5, mylibrary::TetrominoType::kS);

  SECTION("Initializing S") {
    mylibrary::Location pixels[4] = {mylibrary::Location(4, 1),
                                     mylibrary::Location (5, 1),
                                     mylibrary::Location(5, 0),
                                     mylibrary::Location(6, 0)};
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }
}

TEST_CASE("Tetromino Z") {
  mylibrary::Tetromino tetromino
      (5, mylibrary::TetrominoType::kZ);

  SECTION("Initializing Z") {
    mylibrary::Location pixels[4] = {mylibrary::Location(6, 1),
                                     mylibrary::Location (5, 1),
                                     mylibrary::Location(5, 0),
                                     mylibrary::Location(4, 0)};
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }
}