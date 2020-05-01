//
// Created by Teresa Dong on 4/20/20.
//
#include <catch2/catch.hpp>

#include "mylibrary/engine.h"


TEST_CASE("Get Tetromino Piece") {
  tetris::Engine engine(5, 5);

  //The tetromino should be existent and we should be able to get its type
  tetris::Tetromino tetromino = engine.GetTetromino();
  REQUIRE_NOTHROW(tetromino.GetTetrominoType());
}

TEST_CASE("Initial states") {
  tetris::Engine engine(3, 3);

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
  tetris::Engine engine(5, 5);

  SECTION("Screen updates with placed tetrominoes") {
    //Move the current tetromino down the screen
    engine.UpdateMovement(tetris::Movement::kFall);

    std::vector<std::vector<cinder::Color>> screen = engine.GetScreen();
    size_t pixel_count = 0;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (screen[i][j] != cinder::Color(1, 1, 1)) {
          pixel_count++;
        }
      }
    }

    // There should be at least one tetromino that is already placed
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

    engine.UpdateMovement(tetris::Movement::kRight);

    REQUIRE(engine.GetTetromino().GetPixelLocation(1).Row()
                == start_location + 1);
  }
}

TEST_CASE("Movement with Boundary Conflicts") {
  tetris::Engine engine(5, 5);

  SECTION("Left Boundary Conflict") {
    //Move our tetromino as left as we can.
    for (int i = 0; i < 5; i++) {
      engine.UpdateMovement(tetris::Movement::kLeft);
    }

    for (int i = 0; i < 4; i++) {
      tetris::Location pixel_loc = engine.GetTetromino().GetPixelLocation(i);
      //Make sure our tetromino is within the left-right bounds of the screen.
      REQUIRE(pixel_loc.Row() >= 0);
    }
  }

  SECTION("Right Boundary Conflict") {
    //Move our tetromino as left as we can.
    for (int i = 0; i < 5; i++) {
      engine.UpdateMovement(tetris::Movement::kRight);
    }

    for (int i = 0; i < 4; i++) {
      tetris::Location pixel_loc = engine.GetTetromino().GetPixelLocation(i);
      //Make sure our tetromino is within the left-right bounds of the screen.
      REQUIRE(pixel_loc.Row() < 5);
    }
  }

  SECTION("Bottom Boundary Conflict") {
    //Move our tetromino as left as we can.
    for (int i = 0; i < 5; i++) {
      engine.UpdateMovement(tetris::Movement::kDown);
    }

    //We don't need to worry that engine generates a new tetromino because
    //we're not stepping the engine - just moving the tetromino.
    for (int i = 0; i < 4; i++) {
      tetris::Location pixel_loc = engine.GetTetromino().GetPixelLocation(i);
      // Make sure our tetromino is within the left-right bounds of the screen.
      REQUIRE(pixel_loc.Col() >= 0);
    }
  }
}

TEST_CASE("Other Tetrominoes conflict") {
  //Create a screen that matches the size of our game's width and height
  std::vector<std::vector<cinder::Color>> screen;
  screen.resize(5, std::vector<cinder::Color>
      (5, cinder::Color(1, 1, 1)));

  //Create our column barrier as the second column from the left
  for (int i = 0; i < 5; i++) {
    screen[i][1] = cinder::Color(0, 0, 0);
  }

  tetris::Engine engine
  (8, 5, screen, tetris::TetrominoType::kO);

  SECTION("Left movement conflict") {
    //Move our tetromino as left as we can.
    for (int i = 0; i < 5; i++) {
      engine.UpdateMovement(tetris::Movement::kLeft);
    }

    for (int i = 0; i < 4; i++) {
      tetris::Location pixel_loc = engine.GetTetromino().GetPixelLocation(i);
      //Our tetromino should not be able to move past the barrier we made at
      //the second column from the left
      REQUIRE(pixel_loc.Row() > 1);
    }
  }
}

TEST_CASE("Ending and Restarting Game") {
  //Make our whole screen filled with black pixels representing
  //tetrominoes > the game must end
  std::vector<std::vector<cinder::Color>> screen;
  screen.resize(5, std::vector<cinder::Color>
      (8, cinder::Color(0, 0, 0)));

  //Create a engine with this screen and the game should end
  tetris::Engine engine
  (8, 5, screen, tetris::TetrominoType::kO);

  engine.Step();

  REQUIRE(engine.IsGameOver());

  //Our tetromino should not continue to fall if the game is over
  tetris::Tetromino initial_tetromino = engine.GetTetromino();
  engine.Step();

  for (int i = 0; i < 4; i++) {
    REQUIRE(engine.GetTetromino().GetPixelLocation(i) ==
            initial_tetromino.GetPixelLocation(i));
  }

  //Now let's restart our game and check for it's states
  engine.Reset();

  //The game should now not be over
  REQUIRE(!engine.IsGameOver());

  screen = engine.GetScreen();
  //Every line of pixels should be white
  for (const auto& i : screen) {
    REQUIRE(i == std::vector<cinder::Color>
        (8, cinder::Color(1, 1, 1)));
  }
}

TEST_CASE("Rotation Conflicts") {
  std::vector<std::vector<cinder::Color>> screen;
  screen.resize(5, std::vector<cinder::Color>
      (8, cinder::Color(1, 1, 1)));

  SECTION("Conflict with screen boundary: Tetromino I") {
    // We do not have pixels since we're testing for screen boundary so we
    // do not need to modify our screen

    // Start our game with TetrominoType I
    // Reasoning for choosing TetrominoType I: It's a tetromino that has
    // rotation conflict. Some tetrominoes don't have this issue. We want to
    // ensure that we can test for this, so we don't want to generate a random
    // tetromino.
    tetris::Engine engine
        (8, 5, screen, tetris::TetrominoType::kI);

    // Rotate our Tetromino I so that it's vertical
    engine.UpdateMovement(tetris::Movement::kRotate);

    // Move our tetromino to the edge of the screen on the right
    for (int i = 0; i < 4; i++) {
      engine.UpdateMovement(tetris::Movement::kRight);
    }

    // Keep track of the location of each pixel in our tetromino
    tetris::Tetromino initial_tetromino = engine.GetTetromino();

    // Try to rotate it > check that all locations are still the same. It
    // shouldn't be able to rotate.
    engine.UpdateMovement(tetris::Movement::kRotate);

    for (int i = 0; i < 4; i++) {
      REQUIRE(engine.GetTetromino().GetPixelLocation(i)
      == initial_tetromino.GetPixelLocation(i));
    }
  }

  SECTION("Conflict with other tetromino") {
    // Create our column barrier as the second column from the left
    for (int i = 0; i < 5; i++) {
      screen[i][1] = cinder::Color(0, 0, 0);
    }

    tetris::Engine engine
        (8, 5, screen, tetris::TetrominoType::kI);

    // Rotate our Tetromino I so that it's vertical
    engine.UpdateMovement(tetris::Movement::kRotate);

    // Move our tetromino as left as we can > it should be touching the barrier
    // From a previous test, we already know that our tetromino will not cross
    // this vertical barrier.
    for (int i = 0; i < 4; i++) {
      engine.UpdateMovement(tetris::Movement::kLeft);
    }

    // Lets save our current location of our tetromino
    tetris::Tetromino initial_tetromino = engine.GetTetromino();

    // Try to rotate it > check that all locations are still the same. It
    // shouldn't be able to rotate.
    engine.UpdateMovement(tetris::Movement::kRotate);

    for (int i = 0; i < 4; i++) {
      REQUIRE(engine.GetTetromino().GetPixelLocation(i)
                  == initial_tetromino.GetPixelLocation(i));
    }
  }
}

TEST_CASE("Score Updates with Clearing Lines") {
  //Create a empty screen
  std::vector<std::vector<cinder::Color>> screen;
  screen.resize(3, std::vector<cinder::Color>
      (8, cinder::Color(1, 1, 1)));

  //Add a full line on the bottom
  screen.push_back(std::vector<cinder::Color>
                       (8, cinder::Color(0, 0, 0)));

  //Add a full line in a row other than the bottom
  screen.insert(screen.begin(), std::vector<cinder::Color>
      (8, cinder::Color(0, 0, 0)));

  tetris::Engine engine
      (8, 5, screen, tetris::TetrominoType::kI);

  engine.Step();

  //The full lines should be recognized. Our score should be two bc we added two
  //full lines.
  REQUIRE(engine.GetScore() == 2);

  //Our screen should still have 5 rows of 8 pixels.
  screen = engine.GetScreen();
  REQUIRE(screen.size() == 5);

  for (int i = 0; i < 5; i++) {
    REQUIRE(screen.at(i).size() == 8);
  }

  //All pixels should now be white(empty)

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 8; j++) {
      REQUIRE(screen.at(i).at(j) == cinder::Color(1, 1, 1));
    }
  }
}