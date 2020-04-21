//
// Created by Teresa Dong on 4/18/20.
//

#include "mylibrary/engine.h"

#include <utility>

namespace mylibrary {

Engine::Engine(size_t width, size_t height)
    : width_{width}, height_{height}, tetromino_(width / 2) {
  screen_.resize(height, std::vector<bool>( width,false ));
  game_over_ = false;
  score_ = 0;
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

  ClearedRow();
}

void Engine::GenerateNewTetromino() {
  AddTetrominoToScreen();
  tetromino_ = Tetromino(width_ / 2);
  if (HasMovementConflict(0, 0)) {
    tetromino_.MoveTetromino(0, -1);
    if (HasMovementConflict(0, 0)) {
      game_over_ = true;
    }
  }
}

void Engine::AddTetrominoToScreen() {
  //Make each location where the tetromino landed as true in our screen
  for (int i = 0; i < kPixelsInTetromino; i ++) {
    int x_loc = tetromino_.GetPixelLocation(i).Row();
    int y_loc = tetromino_.GetPixelLocation(i).Col();

    //If this pixel is above the screen, don't add it to the screen.
    if (y_loc < 0) {
      continue;
    }
    screen_[y_loc][x_loc] = true;
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
      bool fallen = HasMovementConflict(0, 1);
      while (!fallen) {
        tetromino_.MoveTetromino(0, 1);
        fallen = HasMovementConflict(0, 1);
      }

      //Generate a new tetromino, this one has reached a surface
      Step();
      break;
  }
}

bool Engine::ClearedRow() {
  size_t rows_cleared = 0;

  for (auto row = screen_.begin(); row != screen_.end(); ++row) {

    //If this row has all true values, it can be cleared
    if (!(std::find(row->begin(), row->end(), false) != row->end())) {
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
    screen_.insert(screen_.begin(), std::vector<bool>(width_,false));
  }

  score_ += rows_cleared;

  return true;
}

bool Engine::HasMovementConflict(int horizontal_amt, int vertical_amt) {
  for (int i = 0; i < kPixelsInTetromino; i++) {
    int pixel_row = tetromino_.GetPixelLocation(i).Row() + horizontal_amt;
    int pixel_col = tetromino_.GetPixelLocation(i).Col() + vertical_amt;

    //If this pixel is above the screen, disregard it. It will be handled by
    //game ending mechanism
    if (pixel_col < 0) {
      continue;
    }

    if (pixel_col > height_ - 1 || pixel_row < 0 || pixel_row > width_ - 1
        || screen_[pixel_col][pixel_row]) {
      return true;
    }
  }

  return false;
}

bool Engine::HasRotationConflict() {
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

    //Check if it conflicts with any tetrominoes
    if (screen_[x_loc][y_loc]) {
      return true;
    }
  }

  return false;
}

Tetromino Engine::GetTetromino() {
  return tetromino_;
}

std::vector<std::vector<bool>> Engine::GetScreen() {
  return screen_;
}

bool Engine::IsGameOver() {
  return game_over_;
}

size_t Engine::GetScore() {
  return score_;
}

}   // namespace mylibrary

