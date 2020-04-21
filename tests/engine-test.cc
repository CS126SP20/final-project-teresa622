//
// Created by Teresa Dong on 4/20/20.
//
#include <catch2/catch.hpp>

#include "mylibrary/engine.h"


TEST_CASE("Get Tetromino Piece") {
  mylibrary::Engine engine(5, 5);

  //The tetromino should be existent and we should be able to get its type
  mylibrary::Tetromino tetromino = engine.GetTetromino();
  REQUIRE_NOTHROW(tetromino.GetTetrominoType());
}

TEST_CASE("Screen should initially be empty") {
  mylibrary::Engine engine(3, 3);
  std::vector<std::vector<bool>> screen = engine.GetScreen();

  //Loop through the screen and check that all values are initially false
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      REQUIRE(!screen[i][j]);
    }
  }
}

TEST_CASE("Screen updates with placed tetrominoes") {
  mylibrary::Engine engine(5, 5);

  //Move the current tetromino down the screen
  for (int i = 0; i < 4; i++) {
    engine.UpdateMovement(mylibrary::Movement::kDown);
  }

  engine.Step();

  std::vector<std::vector<bool>> screen = engine.GetScreen();
  size_t pixel_count = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (screen[i][j]) {
        pixel_count++;
      }
    }
  }

  //There should be at least one tetromino that is already placed
  REQUIRE(pixel_count >= 4);
}

TEST_CASE("Step moves the tetromino down") {
  mylibrary::Engine engine(5, 5);

  //Get the start column of one of the pixels
  int start_location = engine.GetTetromino().GetPixelLocation(1).Col();

  engine.Step();

  //The new location of this pixel should be one column below
  REQUIRE(engine.GetTetromino().GetPixelLocation(1).Col()
  == start_location + 1);
}

TEST_CASE("Move Tetromino") {
  mylibrary::Engine engine(5, 5);

  //Get the start location of one of the pixels
  int start_location = engine.GetTetromino().GetPixelLocation(1).Row();

  engine.UpdateMovement(mylibrary::Movement::kRight);

  REQUIRE(engine.GetTetromino().GetPixelLocation(1).Row()
  == start_location + 1);
}