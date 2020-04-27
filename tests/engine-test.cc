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

TEST_CASE("Initial states") {
  mylibrary::Engine engine(3, 3);

  SECTION("The screen should be empty") {
    std::vector<std::vector<cinder::Color>> screen = engine.GetScreen();

    //Loop through the screen and check that all pixels are initially white
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        REQUIRE(screen[i][j] == cinder::Color(1, 1, 1));
      }
    }
  }

  SECTION("The score should be 0") {
    REQUIRE(engine.GetScore() == 0);
  }

  SECTION("A color theme is selected") {
    size_t color_theme = engine.GetColorThemeIndex();
    REQUIRE(color_theme >= 0);
    REQUIRE(color_theme < 6);
  }

  SECTION("The game should not be over") {
    REQUIRE(!engine.IsGameOver());
  }
}

TEST_CASE("Tetromino movements") {
  mylibrary::Engine engine(5, 5);

  SECTION("Screen updates with placed tetrominoes") {
    //Move the current tetromino down the screen
    engine.UpdateMovement(mylibrary::Movement::kFall);

    std::vector<std::vector<cinder::Color>> screen = engine.GetScreen();
    size_t pixel_count = 0;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (screen[i][j] != cinder::Color(1, 1, 1)) {
          pixel_count++;
        }
      }
    }

    //There should be at least one tetromino that is already placed
    REQUIRE(pixel_count >= 4);
  }

  SECTION("Step moves the tetromino down") {
    //Get the start column of one of the pixels
    int start_location = engine.GetTetromino().GetPixelLocation(1).Col();

    engine.Step();

    //The new location of this pixel should be one column below
    REQUIRE(engine.GetTetromino().GetPixelLocation(1).Col()
                == start_location + 1);
  }

  SECTION("Move Tetromino Right") {
    //Get the start location of one of the pixels
    int start_location = engine.GetTetromino().GetPixelLocation(1).Row();

    engine.UpdateMovement(mylibrary::Movement::kRight);

    REQUIRE(engine.GetTetromino().GetPixelLocation(1).Row()
                == start_location + 1);
  }
}

TEST_CASE("Movement with Boundary Conflicts") {
  mylibrary::Engine engine(5, 5);

  SECTION("Left Boundary Conflict") {
    //Move our tetromino as left as we can.
    for (int i = 0; i < 5; i++) {
      engine.UpdateMovement(mylibrary::Movement::kLeft);
    }

    for (int i = 0; i < 4; i++) {
      mylibrary::Location pixel_loc = engine.GetTetromino().GetPixelLocation(i);
      //Make sure our tetromino is within the left-right bounds of the screen.
      REQUIRE(pixel_loc.Row() >= 0);
    }
  }

  SECTION("Right Boundary Conflict") {
    //Move our tetromino as left as we can.
    for (int i = 0; i < 5; i++) {
      engine.UpdateMovement(mylibrary::Movement::kRight);
    }

    for (int i = 0; i < 4; i++) {
      mylibrary::Location pixel_loc = engine.GetTetromino().GetPixelLocation(i);
      //Make sure our tetromino is within the left-right bounds of the screen.
      REQUIRE(pixel_loc.Row() < 5);
    }
  }

  SECTION("Bottom Boundary Conflict") {
    //Move our tetromino as left as we can.
    for (int i = 0; i < 5; i++) {
      engine.UpdateMovement(mylibrary::Movement::kDown);
    }

    //We don't need to worry that engine generates a new tetromino because
    //we're not stepping the engine - just moving the tetromino.
    for (int i = 0; i < 4; i++) {
      mylibrary::Location pixel_loc = engine.GetTetromino().GetPixelLocation(i);
      //Make sure our tetromino is within the left-right bounds of the screen.
      REQUIRE(pixel_loc.Col() >= 0);
    }
  }
}

TEST_CASE("Other Tetrominoes conflict") {
  //Create our column barrier as the second column from the right
  std::vector<std::vector<cinder::Color>> screen;
  screen.resize(5, std::vector<cinder::Color>
      (5, cinder::Color(1, 1, 1)));
  for (int i = 0; i < 5; i++) {
    screen[i][1] = cinder::Color(0, 0, 0);
  }

  mylibrary::Engine engine(8, 5, screen);

  SECTION("Movement conflict") {
    //Move our tetromino as left as we can.
    for (int i = 0; i < 5; i++) {
      engine.UpdateMovement(mylibrary::Movement::kLeft);
    }

    for (int i = 0; i < 4; i++) {
      mylibrary::Location pixel_loc = engine.GetTetromino().GetPixelLocation(i);
      //Our tetromino should not be able to move past the barrier we made at
      // the second column from the left
      REQUIRE(pixel_loc.Row() >= 2);
    }
  }
}

TEST_CASE("Game Over Detected") {
  std::vector<std::vector<cinder::Color>> screen;
  screen.resize(5, std::vector<cinder::Color>
      (5, cinder::Color(1, 1, 1)));
  for (int i = 0; i < 5; i++) {
    screen[0][i] = cinder::Color(0, 0, 0);
  }

  mylibrary::Engine engine(8, 5, screen);

  engine.Step();

  REQUIRE(engine.IsGameOver());
}