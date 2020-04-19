//
// Created by Teresa Dong on 4/18/20.
//

#include "mylibrary/engine.h"

#include <iostream>
#include <utility>

namespace mylibrary {

Engine::Engine(size_t width, size_t height)
    : width_{width}, height_{height}, tetromino_(width / 2){
  screen_.resize(height, std::vector<bool>( width,false ));
}

void Engine::Step() {
  //Check if any of the contact pixels have reached a surface
  //Else drop the piece as usual
  if (!CheckSurfaceContact()) {
    tetromino_.MoveTetromino(0, 1);
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
      tetromino_.MoveTetromino(-1, 0);
      break;
    case Movement::kRight:
      tetromino_.MoveTetromino(1, 0);
      break;
    case Movement::kDown:
      tetromino_.MoveTetromino(0, 1);
      break;
    case Movement::kRotate:
      tetromino_.RotateTetromino();
      break;
  }

  CheckSurfaceContact();
}

bool Engine::CheckSurfaceContact() {
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

