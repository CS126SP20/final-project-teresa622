//
// Created by Teresa Dong on 4/18/20.
//

#ifndef FINALPROJECT_SRC_ENGINE_H_
#define FINALPROJECT_SRC_ENGINE_H_

#include <vector>
#include <cinder/Color.h>
#include "movement.h"
#include "mylibrary/tetromino.h"

namespace tetris {

//The number of pixels in every tetromino piece
const size_t kPixelsInTetromino = 4;

//The color of the locations without tetrominoes are white.
const cinder::Color kWhite(1, 1, 1);

class Engine {
 public:
  /**
   * Engine constructor. Creates a new game engine with the given screen
   * parameters
   * @param width the width of the screen
   * @param height the height of the screen
   */
  Engine(size_t width, size_t height);
   /**
    * Engine constructor. Allows initialization of specific screen to begin with
    * Currently used for testing purposes, but can be used in the future
    * for Tetris games with maps (pixels already on the screen to begin with)
    * @param width the width of the screen
    * @param height the height of the screen
    * @param screen the pixels the screen should be initialized with
    * @param tetromino_type the tetromino to start out with
    */
  Engine(size_t width, size_t height,
      std::vector<std::vector<cinder::Color>> screen,
      TetrominoType tetromino_type);

  /**
   * Executes a time step: moves the tetromino down or creates a new one
   */
  void Step();

  /**
   * Start the game over. Resets all states.
   */
  void Reset();

  /**
   * Updates the location of our tetromino based on the key event triggered
   * by the user.
   * @param movement the type of movement that the user triggered.
   */
  void UpdateMovement(Movement movement);

  //Engine getters
  Tetromino GetTetromino();
  //Returns the screen, which contains all the tetrominoes that have already
  //landed on a surface.
  Tetromino GetProjection();
  std::vector<std::vector<cinder::Color>> GetScreen();
  bool IsGameOver();
  size_t GetScore();
  size_t GetColorThemeIndex();

 private:
  /**
   * The current tetromino has landed on a surface. This adds the tetromino
   * to the screen.
   */
  void AddTetrominoToScreen();

  /**
   * Determines if the given action is illegal (bumps into another tetromino
   * or goes out of the screen bounds)
   * @param horizontal_amt the horizontal amount we want to move
   * @param vertical_amt the vertical amount we want to move
   * @return whether or not this movement is illegal
   */
  bool HasMovementConflict(int horizontal_amt, int vertical_amt);

  /**
   * Determines whether rotating the current tetromino is legal or if it
   * bumps into other tetrominoes or goes out of bounds.
   * @return whether a rotation is legal
   */
  bool HasRotationConflict();

  /**
   * Clears any rows that have been completely filled
   * @return whether or not any rows have been cleared
   */
  bool ClearedRow();

  /**
   * Creates a new Tetromino. Also checks if the game is over (the new tetromino
   * immediately conflicts with other tetrominoes on the screen).
   */
  void GenerateNewTetromino();

 private:
  //The width and height of our game screen. Used to check for illegal moves
  const size_t width_;
  const size_t height_;
  const size_t center_tile_;

  //Stores all the fallen tetrominoes. Used by the app to draw.
  std::vector<std::vector<cinder::Color>> screen_;

  //The tetromino that is falling down
  Tetromino tetromino_;

  //Whether or not the game is over
  bool game_over_;

  //The current score based on how many lines were cleared
  size_t score_;

  //The index of the color theme that corresponds to the kThemes array
  size_t color_theme_index_;
};

}   //namespace tetris

#endif  // FINALPROJECT_SRC_ENGINE_H_
