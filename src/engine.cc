//
// Created by Teresa Dong on 4/18/20.
//

#include "mylibrary/engine.h"

#include <iostream>
#include <utility>

namespace mylibrary {

Engine::Engine(size_t width, size_t height)
    : width_{width}, height_{height}, tetromino_(width / 2){
}

void Engine::Step() {
  for (int i = 0; i < 4; i++) {
    tetromino_.SetPixelLocation(i, tetromino_.GetPixelLocation(i) += Location(0, 1));
  }
}

Tetromino Engine::GetTetromino() {
  return tetromino_;
}

}

