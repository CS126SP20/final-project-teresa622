//
// Created by Teresa Dong on 4/18/20.
//

#include "mylibrary/engine.h"
#include "mylibrary/color_theme.h"
#include <utility>

namespace mylibrary {

Engine::Engine(size_t width, size_t height)
    : width_{width}, height_{height}, game_over_{false}, score_{0},
    tetromino_{0, 0}, center_tile_{width_ / 2} {

  // Fill our screen with all white pixels to start with
  screen_.resize(height, std::vector<cinder::Color>(width, kWhite));

  // Get a random color theme for this game
  color_theme_index_ = GenerateColorThemeIndex();

  tetromino_ = Tetromino(center_tile_, color_theme_index_);
}

Engine::Engine(size_t width, size_t height,
    std::vector<std::vector<cinder::Color>> screen,
    TetrominoType tetromino_type)
  : width_{width}, height_{height}, game_over_{false}, score_{0},
  tetromino_{0, 0}, center_tile_{width_ / 2},

    // Fill our screen with the pixels we were given
  screen_{std::move(screen)} {

  // Get a random color theme for this game
  color_theme_index_ = GenerateColorThemeIndex();

  tetromino_ = Tetromino(center_tile_, color_theme_index_, tetromino_type);
}

size_t Engine::GenerateColorThemeIndex() {
  // Credit: See tetromino.cc
  struct timespec ts{};
  clock_gettime(CLOCK_MONOTONIC, &ts);

  /* using nano-seconds instead of seconds */
  srand((time_t)ts.tv_nsec);

  //Generate a random number 0-5
  return rand() % kNumOfThemes;
}

void Engine::Step() {
  if (game_over_) {
    return;
  }

  //Move the tetromino down if possible
  if (!HasMovementConflict(0, 1)) {
    tetromino_.MoveTetromino(0, 1);
  } else {
    //The tetromino cannot be moved down > it has reached a surface.
    GenerateNewTetromino();
  }

  //Clear any rows that have been filled
  ClearedRow();
}

void Engine::GenerateNewTetromino() {
  //Add our current tetromino to the screen and create a new one.
  AddTetrominoToScreen();
  tetromino_ = Tetromino(width_ / 2, color_theme_index_);

  //Determine if the newly generated tetromino immediately causes conflict
  //with the other tetrominoes on the screen.
  if (HasMovementConflict(0, 0)) {

    //The tetromino is resting half on the screen and half off.
    tetromino_.MoveTetromino(0, -1);
    if (HasMovementConflict(0, 0)) {

      //The tetromino is completely above the screen so the game is over.
      game_over_ = true;
    }
  }
}

void Engine::AddTetrominoToScreen() {
  //Make each location where the tetromino landed with its color
  for (int i = 0; i < kPixelsInTetromino; i ++) {
    int x_loc = tetromino_.GetPixelLocation(i).Row();
    int y_loc = tetromino_.GetPixelLocation(i).Col();

    //If this pixel is above the screen, don't add it to the screen.
    if (y_loc < 0) {
      continue;
    }

    screen_[y_loc][x_loc] = tetromino_.GetColor();
  }
}

void Engine::UpdateMovement(Movement movement) {
  //In every case, check first if this intended movement is illegal.
  //If not, then proceed to move the tetromino
  switch (movement) {
    case Movement::kLeft:
      if (!HasMovementConflict(-1, 0)) {
        tetromino_.MoveTetromino(-1, 0);
      }
      break;
    case Movement::kRight:
      if (!HasMovementConflict(1, 0)) {
        tetromino_.MoveTetromino(1, 0);
      }
      break;
    case Movement::kDown:
      if (!HasMovementConflict(0, 1)) {
        tetromino_.MoveTetromino(0, 1);
      }
      break;
    case Movement::kRotate:
      if (!HasRotationConflict()) {
        tetromino_.RotateTetromino();
      }
      break;
    case Movement::kFall:
      tetromino_ = GetProjection();

      //Generate a new tetromino, this one has reached a surface
      Step();
      break;
  }
}

Tetromino Engine::GetProjection() {
  //Store the current location of the tetromino
  Tetromino projection_tetromino = tetromino_;\

  //Now drop our tetromino until it has landed
  bool fallen = HasMovementConflict(0, 1);
  while (!fallen) {
    tetromino_.MoveTetromino(0, 1);
    fallen = HasMovementConflict(0, 1);
  }

  //Switch the tetrominoes
  Tetromino temp = tetromino_;
  tetromino_ = projection_tetromino;
  projection_tetromino = temp;

  return projection_tetromino;
}

bool Engine::ClearedRow() {
  size_t rows_cleared = 0;

  //Loop through each row and check if it is full (can be cleared)
  for (auto row = screen_.begin(); row != screen_.end(); ++row) {

    //If this row has all color values, it can be cleared
    if (!(std::find(row->begin(), row->end(), kWhite) != row->end())) {
      screen_.erase(row--);
      rows_cleared++;
    }
  }

  if (rows_cleared == 0) {
    return false;
  }

  //Add in empty rows for the rows we cleared. We want to keep screen_ the
  //same size
  for (int i = 0; i < rows_cleared; i++) {
    screen_.insert(screen_.begin(),
        std::vector<cinder::Color>(width_,kWhite));
  }

  //The number of rows cleared is added to our score.
  score_ += rows_cleared;

  return true;
}

bool Engine::HasMovementConflict(int horizontal_amt, int vertical_amt) {
  //Loop through each pixel and determine if this movement is legal
  for (int i = 0; i < kPixelsInTetromino; i++) {
    int pixel_row = tetromino_.GetPixelLocation(i).Row() + horizontal_amt;
    int pixel_col = tetromino_.GetPixelLocation(i).Col() + vertical_amt;

    //If this pixel is above the screen, disregard it. It will be handled by
    //game ending detector
    if (pixel_col < 0) {
      continue;
    }

    //This movement is illegal if it goes below the screen or past the
    //vertical bounds of the screen
    if (pixel_col > height_ - 1 || pixel_row < 0 || pixel_row > width_ - 1
        || screen_[pixel_col][pixel_row] != kWhite) {
      return true;
    }
  }

  return false;
}

bool Engine::HasRotationConflict() {
  //If the tetromino is O, there is no rotation. > return true so that it
  //won't be rotated.
  if (tetromino_.GetTetrominoType() == TetrominoType::kO) {
    return true;
  }

  //Get the rotation point from tetromino to calculate the rotation locations
  Location rotation_loc = tetromino_.GetRotationPoint();
  int rot_x = rotation_loc.Row();
  int rot_y = rotation_loc.Col();

  for (int i = 0; i < kPixelsInTetromino; i++) {
    int y_loc = (rot_x + rot_y) - tetromino_.GetPixelLocation(i).Col();
    int x_loc = (rot_y - rot_x) + tetromino_.GetPixelLocation(i).Row();

    //Check if it crosses the screen boundaries
    if (y_loc > width_ - 1 || y_loc < 0 || x_loc > height_ - 1) {
      return true;
    }

    //Check if it conflicts with any other tetrominoes
    if (screen_[x_loc][y_loc] != kWhite) {
      return true;
    }
  }

  return false;
}

void Engine::Reset() {
  game_over_ = {false};
  score_ = {0};
  screen_.clear();
  screen_.resize(height_, std::vector<cinder::Color>(width_, kWhite));
  GenerateColorThemeIndex();
  tetromino_ = Tetromino(center_tile_, color_theme_index_);
}

//Game engine getters
Tetromino Engine::GetTetromino() {
  return tetromino_;
}

std::vector<std::vector<cinder::Color>> Engine::GetScreen() {
  return screen_;
}

bool Engine::IsGameOver() {
  return game_over_;
}

size_t Engine::GetScore() {
  return score_;
}

size_t Engine::GetColorThemeIndex() {
  return color_theme_index_;
}

}   // namespace mylibrary

