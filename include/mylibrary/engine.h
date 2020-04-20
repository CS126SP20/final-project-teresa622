//
// Created by Teresa Dong on 4/18/20.
//

#ifndef FINALPROJECT_SRC_ENGINE_H_
#define FINALPROJECT_SRC_ENGINE_H_

#include <vector>

#include "mylibrary/tetromino.h"
#include "mylibrary/movement.h"

namespace mylibrary {

class Engine {
 public:

  Engine(size_t width, size_t height);

  // Executes a time step: moves the tetromino
  void Step();

  // Start the game over
  void Reset();

  Tetromino GetTetromino();

  std::vector<std::vector<bool>> GetScreen();

  void UpdateMovement(Movement movement);

 private:
  void AddTetrominoToScreen();
  bool CheckSurfaceContact();
  bool MovementConflict(int horizontal_amt, int vertical_amt);
  bool RotationConflict();

 private:
  const size_t width_;
  const size_t height_;
  std::vector<std::vector<bool>> screen_;
  Tetromino tetromino_;
  bool drop_buffer_;
};

}   //namespace mylibrary

#endif  // FINALPROJECT_SRC_ENGINE_H_
