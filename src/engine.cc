//
// Created by Teresa Dong on 4/18/20.
//

#include "mylibrary/engine.h"

#include <utility>

namespace mylibrary {

Engine::Engine(size_t width, size_t height)
    : width_{width}, height_{height}, tetromino_(width / 2){
  screen_.resize(height, std::vector<bool>( width,false ));
}

void Engine::Step() {
  //Check if any of the contact pixels have reached a surface
  //Else drop the piece as usual
  if (!HasSurfaceContact()) {
    tetromino_.MoveTetromino(0, 1);
  } else {
    ClearedRow();
  }
}

void Engine::AddTetrominoToScreen() {
  for (int i = 0; i < kPixelsInTetromino; i ++) {
    int x_loc = tetromino_.GetPixelLocation(i).Row();
    int y_loc = tetromino_.GetPixelLocation(i).Col();
    screen_[y_loc][x_loc] = true;
  }
}

void Engine::UpdateMovement(Movement movement) {
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
  }

  if (HasSurfaceContact()) {
    ClearedRow();
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

  return true;
}

bool Engine::HasMovementConflict(int horizontal_amt, int vertical_amt) {
  for (int i = 0; i < kPixelsInTetromino; i++) {
    int pixel_row = tetromino_.GetPixelLocation(i).Row() + horizontal_amt;
    int pixel_col = tetromino_.GetPixelLocation(i).Col() + vertical_amt;
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

bool Engine::HasSurfaceContact() {
  std::vector<int> contact_indexes = tetromino_.FindContactPixels();
  for (int & index : contact_indexes) {
    int col = tetromino_.GetPixelLocation(index).Col();
    int row = tetromino_.GetPixelLocation(index).Row();

    //Tetromino has touched a surface
    //(bottom of the screen or another tetromino)
    if (col == height_ - 1 || screen_[col + 1][row]) {
      AddTetrominoToScreen();
      //Make a new tetromino
      tetromino_ = Tetromino(width_ / 2);
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

}   // namespace mylibrary

