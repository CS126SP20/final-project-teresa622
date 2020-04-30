//
// Created by Teresa Dong on 4/17/20.
//

#ifndef FINALPROJECT_SRC_TETROMINO_H_
#define FINALPROJECT_SRC_TETROMINO_H_

#include <vector>

#include "mylibrary/location.h"
#include "mylibrary/tetromino_type.h"
#include "mylibrary/color_theme.h"
#include <cinder/Color.h>

namespace mylibrary {

// The constant number of types of tetrominoes
const size_t kNumTetrominoTypes = 7;

// The rotation point is always the 2nd element in our array
const size_t kRotationPointIndex = 1;

// The list of different tetromino types
const TetrominoType kTetrominoTypes[kNumTetrominoTypes] =
    {TetrominoType::kI, TetrominoType::kJ,
     TetrominoType::kL, TetrominoType::kO,
     TetrominoType::kT, TetrominoType::kS,
     TetrominoType::kZ};

class Tetromino {
 public:
  /**
   * Tetromino constructor. Used by the game engine to create a new tetromino.
   * @param center_tile the location of the center tile so our tetromino can be
   * placed in the middle of the screen.
   */
  Tetromino(int center_tile, size_t theme_index);

  /**
   * Tetromino constructor. Used mostly for testing.
   * @param center_tile the location of the center of the screen width-wise
   * @param tetromino_type the type of tetromino that should be created.
   */
  Tetromino(int center_tile, size_t theme_index, TetrominoType tetromino_type);

  /**
   * Translate each pixel of our tetromino
   * @param horizontal_amount the horizontal amount our tetromino should move
   * @param vertical_amount the vertical amount our tetromino should move
   */
  void MoveTetromino(int horizontal_amount, int vertical_amount);

  /**
   * Rotates our tetromino around the rotation point
   */
  void RotateTetromino();

  // Tetromino getters
  Location GetPixelLocation(size_t index);
  Location GetRotationPoint();
  TetrominoType GetTetrominoType();
  cinder::Color GetColor();

 private:
  /**
   * Initializes the location of each pixel in our tetromino depending on the
   * tetromino type.
   * Constructor helper function
   * @param center_tile the center of our screen width-wise
   */
  void InitializePixels(int center_tile);

  /**
   * Generates a random number 0-6 for a tetromino type
   * @return the number that is the index of the tetromino type we are creating
   */
  static size_t GenerateRandTetrominoIndex();

  // Generates each type of tetromino
  void GenerateI(int center_tile);
  void GenerateJ(int center_tile);
  void GenerateL(int center_tile);
  void GenerateO(int center_tile);
  void GenerateT(int center_tile);
  void GenerateS(int center_tile);
  void GenerateZ(int center_tile);

 private:
  // Holds the Location of each pixel in our tetromino
  Location pixels_[4] = {Location(0,0), Location(0,0),
                        Location(0,0), Location(0,0)};

  // Saves the type of tetromino this instance is
  TetrominoType tetromino_type_;

  // The color of the tetromino piece
  cinder::Color color_;

};

}
#endif  // FINALPROJECT_SRC_TETROMINO_H_
