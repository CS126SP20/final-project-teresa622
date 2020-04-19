//
// Created by Teresa Dong on 4/18/20.
//

#ifndef FINALPROJECT_SRC_ENGINE_H_
#define FINALPROJECT_SRC_ENGINE_H_

#include <cstddef>
#include <vector>

#include "mylibrary/tetromino.h"
namespace mylibrary {

class Engine {
  const size_t kPixelsInTetromino = 4;
 public:
  Engine(size_t width, size_t height);

  // Executes a time step: moves the tetromino
  void Step();

  // Start the game over
  void Reset();

  Tetromino GetTetromino();

  std::vector<std::vector<bool>> GetScreen();

 private:
  void AddTetrominoToScreen();
 private:
  const size_t width_;
  const size_t height_;
  std::vector<std::vector<bool>> screen_;
  Tetromino tetromino_;
};

}   //namespace mylibrary

#endif  // FINALPROJECT_SRC_ENGINE_H_
