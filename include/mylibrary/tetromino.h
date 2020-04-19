//
// Created by Teresa Dong on 4/17/20.
//

#ifndef FINALPROJECT_SRC_TETROMINO_H_
#define FINALPROJECT_SRC_TETROMINO_H_
#include <vector>
#include "mylibrary/location.h"
#include "mylibrary/tetromino_type.h"

namespace mylibrary {
const int kNumTetrominoTypes = 7;
const TetrominoType kTetrominoTypes[kNumTetrominoTypes] =
    {TetrominoType::kI, TetrominoType::kJ,
     TetrominoType::kL, TetrominoType::kO,
     TetrominoType::kT, TetrominoType::kS,
     TetrominoType::kZ};

class Tetromino {
 public:
  explicit Tetromino(int center_tile);
  Location GetPixelLocation(size_t index);
  void SetPixelLocation(size_t index, Location loc);
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
  TetrominoType tetromino_type_;

};

}
#endif  // FINALPROJECT_SRC_TETROMINO_H_
