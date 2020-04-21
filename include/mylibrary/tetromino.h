//
// Created by Teresa Dong on 4/17/20.
//

#ifndef FINALPROJECT_SRC_TETROMINO_H_
#define FINALPROJECT_SRC_TETROMINO_H_

#include <vector>

#include "mylibrary/location.h"
#include "mylibrary/tetromino_type.h"

namespace mylibrary {
const size_t kPixelsInTetromino = 4;
const size_t kNumTetrominoTypes = 7;
const size_t rotation_point_index = 1;
const TetrominoType kTetrominoTypes[kNumTetrominoTypes] =
    {TetrominoType::kI, TetrominoType::kJ,
     TetrominoType::kL, TetrominoType::kO,
     TetrominoType::kT, TetrominoType::kS,
     TetrominoType::kZ};

class Tetromino {
 public:
  explicit Tetromino(int center_tile);
  Tetromino(int center_tile, TetrominoType tetromino_type);
  Location GetPixelLocation(size_t index);
  void MoveTetromino(int horizontal_amount, int vertical_amount);
  void RotateTetromino();
  Location GetRotationPoint();
  TetrominoType GetTetrominoType();
  std::vector<int> FindContactPixels();

 private:
  void InitializePixels_(int center_tile);
  void GenerateI(int center_tile);
  void GenerateJ(int center_tile);
  void GenerateL(int center_tile);
  void GenerateO(int center_tile);
  void GenerateT(int center_tile);
  void GenerateS(int center_tile);
  void GenerateZ(int center_tile);

 private:
  Location pixels[4] = {Location(0,0), Location(0,0),
                        Location(0,0), Location(0,0)};
  std::vector<int> contact_pixel_indexes;
  bool rotated = true;
  TetrominoType tetromino_type_;
};

}
#endif  // FINALPROJECT_SRC_TETROMINO_H_
