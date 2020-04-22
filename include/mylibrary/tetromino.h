//
// Created by Teresa Dong on 4/17/20.
//

#ifndef FINALPROJECT_SRC_TETROMINO_H_
#define FINALPROJECT_SRC_TETROMINO_H_

#include <vector>

#include "mylibrary/location.h"
#include "mylibrary/tetromino_type.h"
#include <cinder/Color.h>

namespace mylibrary {

//The constant number of types of tetrominoes
const size_t kNumTetrominoTypes = 7;

//The rotation point is always the 2nd element in our array
const size_t rotation_point_index = 1;

//The list of different tetromino types
const TetrominoType kTetrominoTypes[kNumTetrominoTypes] =
    {TetrominoType::kI, TetrominoType::kJ,
     TetrominoType::kL, TetrominoType::kO,
     TetrominoType::kT, TetrominoType::kS,
     TetrominoType::kZ};

//The color theme of the tetrominoes corresponding to the tetromino types array
const cinder::Color kColors[kNumTetrominoTypes] =
    {cinder::Color(0.80, 0.60, 0.79),
     cinder::Color(0.62, 0.76, 0.81),
     cinder::Color(0.62, 0.88, 0.62),
     cinder::Color(1, 0.72, 0.17),
     cinder::Color(1, 0.40, 0.39),
     cinder::Color(1, 0.71, 0.71),
     cinder::Color(1, 0.91,0.37)};

class Tetromino {
 public:
  /**
   * Tetromino constructor. Used by the game engine to create a new tetromino.
   * @param center_tile the location of the center tile so our tetromino can be
   * placed in the middle of the screen.
   */
  explicit Tetromino(int center_tile);

  /**
   * Tetromino constructor. Used mostly for testing.
   * @param center_tile the location of the center of the screen width-wise
   * @param tetromino_type the type of tetromino that should be created.
   */
  Tetromino(int center_tile, TetrominoType tetromino_type);

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

  //Tetromino getters
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

  //Generates each type of tetromino
  void GenerateI(int center_tile);
  void GenerateJ(int center_tile);
  void GenerateL(int center_tile);
  void GenerateO(int center_tile);
  void GenerateT(int center_tile);
  void GenerateS(int center_tile);
  void GenerateZ(int center_tile);

 private:
  //Holds the Location of each pixel in our tetromino
  Location pixels[4] = {Location(0,0), Location(0,0),
                        Location(0,0), Location(0,0)};

  //Saves the type of tetromino this instance is
  TetrominoType tetromino_type_;

  //The color of the tetromino piece
  cinder::Color color_;
};

}
#endif  // FINALPROJECT_SRC_TETROMINO_H_
