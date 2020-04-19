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
  std::vector<int> contact_indexes = tetromino_.FindContactPixels();

  //Check if any of the contact pixels have reached a surface
  for (int i = 0; i < kPixelsInTetromino; i++) {
    if (std::find(contact_indexes.begin(), contact_indexes.end(), i)
    != contact_indexes.end()) {
      int col = tetromino_.GetPixelLocation(i).Col();
      int row = tetromino_.GetPixelLocation(i).Row();

      //Tetromino has touched a surface
      //(bottom of the screen or another tetromino
      if (col == height_ - 1 || screen_[col + 1][row]) {
        AddTetrominoToScreen();
        //Make a new tetromino
        tetromino_ = Tetromino(width_ / 2);
        return;
      }
    }
  }

  //Else drop the piece as usual
  tetromino_.MoveTetromino(0, 1);
}

void Engine::AddTetrominoToScreen() {
  for (int i = 0; i < kPixelsInTetromino; i ++) {
    int x_loc = tetromino_.GetPixelLocation(i).Row();
    int y_loc = tetromino_.GetPixelLocation(i).Col();
    screen_[y_loc][x_loc] = true;
  }
}

Tetromino Engine::GetTetromino() {
  return tetromino_;
}

std::vector<std::vector<bool>> Engine::GetScreen() {
  return screen_;
}

}   // namespace mylibrary

