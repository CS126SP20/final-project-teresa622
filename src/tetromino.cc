//
// Created by Teresa Dong on 4/17/20.
//

#include "mylibrary/tetromino.h"
#include <vector>
namespace mylibrary {

Tetromino::Tetromino(int center_tile) {
  //Generates a random number from 0 to 7
  size_t random_tetromino_generate = rand() % (kNumTetrominoTypes + 1);
  tetromino_type_ = kTetrominoTypes[random_tetromino_generate];
  InitializePixels_(tetromino_type_, center_tile);
}

void Tetromino::InitializePixels_(TetrominoType tetromino_type, int center_tile) {
  switch (tetromino_type) {
    case TetrominoType::kZ:
      GenerateZ(center_tile);
    case TetrominoType::kS:
      GenerateS(center_tile);
    case TetrominoType::kT:
      GenerateT(center_tile);
    case TetrominoType::kO:
      GenerateO(center_tile);
    case TetrominoType::kL:
      GenerateL(center_tile);
    case TetrominoType::kJ:
      GenerateJ(center_tile);
    case TetrominoType::kI:
      GenerateI(center_tile);
  }
}

Location Tetromino::GetPixelLocation(size_t index) {
  return pixels[index];
}
}