// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "mylibrary/tetromino.h"
#include "mylibrary/tetromino_type.h"


TEST_CASE("Tetromino I") {
  tetris::Tetromino tetromino
  (5, 0, tetris::TetrominoType::kI);

  SECTION("Initializing I") {
    tetris::Location pixels[4] = {
        tetris::Location(3, 1), tetris::Location (4, 1), tetris::Location(5, 1),
        tetris::Location(6, 1)};
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }

  //Tests Move Tetromino here
  SECTION("Move Tetromino: positive values") {
    tetromino.MoveTetromino(3, 1);
    REQUIRE(tetromino.GetPixelLocation(0) == tetris::Location(6, 2));
  }

  SECTION("Move Tetromino: negative values") {
    tetromino.MoveTetromino(-3, -1);
    REQUIRE(tetromino.GetPixelLocation(0) == tetris::Location(0, 0));
  }
}

TEST_CASE("Tetromino J") {
  tetris::Tetromino tetromino
      (5, 0, tetris::TetrominoType::kJ);

  SECTION("Initializing J") {
    tetris::Location pixels[4] = {
        tetris::Location(5, 0), tetris::Location (5, 1), tetris::Location(5, 2),
        tetris::Location(4, 2)};
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }

  SECTION("Get Tetromino Type") {
    REQUIRE(tetromino.GetTetrominoType() == tetris::TetrominoType::kJ);
  }
}

TEST_CASE("Tetromino L") {
  tetris::Tetromino tetromino
      (5, 0, tetris::TetrominoType::kL);

  SECTION("Initializing L") {
    tetris::Location pixels[4] = {
        tetris::Location(5, 0), tetris::Location (5, 1), tetris::Location(5, 2),
        tetris::Location(6, 2)};
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }
}

TEST_CASE("Tetromino O") {
  tetris::Tetromino tetromino
      (5, 0, tetris::TetrominoType::kO);
  tetris::Location pixels[4] = {tetris::Location(4, 0), tetris::Location (5, 0),
                                tetris::Location(4, 1), tetris::Location(5, 1)};

  SECTION("Initializing O") {
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }

  SECTION("Rotating O") {
    //Rotating O should not move any of the pixels
    tetromino.RotateTetromino();
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }
}

TEST_CASE("Tetromino T") {
  tetris::Tetromino tetromino
      (5, 0, tetris::TetrominoType::kT);

  SECTION("Initializing T") {
    tetris::Location pixels[4] = {
        tetris::Location(4, 1), tetris::Location (5, 1), tetris::Location(6, 1),
        tetris::Location(5, 0)};
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }

  //Rotation of Tetromino tested here
  SECTION("Rotate Tetromino") {
    tetromino.RotateTetromino();
    //The rotation point for T tetromino is the center joint that connects
    //the three other pixels
    REQUIRE(tetromino.GetRotationPoint() == tetris::Location(5, 1));
    tetris::Location pixels[4] = {
        tetris::Location(5, 0), tetris::Location (5, 1), tetris::Location(5, 2),
        tetris::Location(6, 1)};
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }
}

TEST_CASE("Tetromino S") {
  tetris::Tetromino tetromino
      (5, 0, tetris::TetrominoType::kS);

  SECTION("Initializing S") {
    tetris::Location pixels[4] = {
        tetris::Location(4, 1), tetris::Location (5, 1), tetris::Location(5, 0),
        tetris::Location(6, 0)};
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }
}

TEST_CASE("Tetromino Z") {
  tetris::Tetromino tetromino
      (5, 0, tetris::TetrominoType::kZ);

  SECTION("Initializing Z") {
    tetris::Location pixels[4] = {
        tetris::Location(6, 1), tetris::Location (5, 1), tetris::Location(5, 0),
        tetris::Location(4, 0)};
    for (int i = 0; i < 4; i++) {
      REQUIRE(tetromino.GetPixelLocation(i) == pixels[i]);
    }
  }
}