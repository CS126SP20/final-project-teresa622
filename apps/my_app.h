// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/audio/Voice.h>

#include "mylibrary/player.h"
#include "mylibrary/engine.h"
#include "mylibrary/leaderboard.h"
#include "mylibrary/tetromino.h"

namespace myapp {

//Constant width and height of the game screen
const size_t kWidth = 12;
const size_t kHeight = 20;

//Constant outline width around each tetromino
const float kOutlineLineWidth = 2;

class MyApp : public cinder::app::App {
 public:
  /**
   * App constructor. Creates an interface for Tetris.
   */
  MyApp();

  /**
   * Applies all the necessary setup for the app.
   */
  void setup() override;

  /**
   * Called regularly to update the app with new game states.
   */
  void update() override;

  /**
   * Draws the game elements onto the app depending on the state of the game.
   */
  void draw() override;

  /**
   * Listens to if the user has pressed any buttons that trigger game updates.
   */
  void keyDown(cinder::app::KeyEvent) override;

 private:
  /**
   * Draws the tetromino on the app screen.
   * draw() helper function
   */
  void DrawTetromino();

  /**
   * Draws the tetrominoes that have already landed on a surface.
   * draw() helper function
   */
  void DrawScreen();

  /**
   * Draws the end screen of the app. Displays the leaderboards and the
   * player's score in the game that just ended.
   * draw() helper function
   */
  void DrawGameOver();

  /**
   * Draws the outline of the falling tetromino on the surface. Allows for
   * easier gameplay.
   */
  void DrawProjection();

  void SetUpSounds();

  /**
   * Prints the text onto the screen with the given parameters
   * @tparam C the Cinder::Color type
   * @param text the text to actually print
   * @param color the color of the text
   * @param size the size the text should be on the screen
   * @param loc where the text should be printed on the screen
   */
  template <typename C>
  void PrintText(const std::string& text, const C& color,
                 const cinder::ivec2& size, const cinder::vec2& loc);

 private:
  //Time tracker to determine when engine_.Step() should be called again
  std::chrono::time_point<std::chrono::system_clock> last_time_;

  tetris::Engine engine_;

  //Interacts with our leaderboard database. Used to draw the top scores
  //in the end screen
  tetris::LeaderBoard leaderboard_;

  //The size of each tile on the app screen
  size_t tile_size_;

  //The user entered name for leaderboard/scoring purposes
  std::string username_;

  //Keeps the leaderboard players
  std::vector<tetris::Player> top_players_;

  //The speed at which the game is updated. Determines how fast the tetrominoes
  //fall down the screen.
  size_t speed_;

  //Tracks if the game over screen is already printed. Allows for lazy printing.
  bool printed_game_over_;

  //Keeps track of if the game has ended and if the game over screen should
  //be drawn.
  bool game_over_;

  //Tracks if the game is paused or not
  bool paused_;

  //The color of the outline around the pixels, depending on the color theme
  cinder::Color outline_color_;

  //The score of the player
  size_t score_;

  //Music and sound effect variables
  cinder::audio::VoiceRef theme_music_;
  cinder::audio::VoiceRef line_sound_;
  cinder::audio::VoiceRef clear_sound_;
  cinder::audio::VoiceRef fall_sound_;
  cinder::audio::VoiceRef game_over_sound_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
