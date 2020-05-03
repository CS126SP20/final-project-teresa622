// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "tetris_app.h"

#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/app/App.h>
#include <cinder/audio/Voice.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <gflags/gflags.h>

#include "mylibrary/color_theme.h"
#include "mylibrary/engine.h"

namespace tetrisapp {

//Used to find the path to access our scoring database
const char kDbPath[] = "tetris.db";

//The number of top scores to display in the game over screen
const int kScoreLimit = 3;

//750 ms is the starting speed of how fast the game updates and how fast the
//tetrominoes drop
const int kStartSpeed = 750;
const size_t kSpeedDecrement = 20;
const size_t kLevel = 7;
const size_t kSpeedLimit = 300;

//Text font defined
#if defined(CINDER_COCOA_TOUCH)
const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial-BoldMT";
const char kDifferentFont[] = "AmericanTypewriter";
#elif defined(CINDER_LINUX)
const char kNormalFont[] = "Arial Unicode MS";
const char kBoldFont[] = "Arial Unicode MS";
const char kDifferentFont[] = "Purisa";
#else
const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial Bold";
const char kDifferentFont[] = "Papyrus";
#endif

//gflags (user modifiable variables through command line) defined
DECLARE_uint32(tilesize);
DECLARE_string(name);

using cinder::app::KeyEvent;

MyApp::MyApp()
  : engine_{kWidth, kHeight},
    leaderboard_{cinder::app::getAssetPath(kDbPath).string()},
    tile_size_{FLAGS_tilesize},
    username_{FLAGS_name},
    speed_{kStartSpeed},
    outline_color_{tetris::kThemeOutline[engine_.GetColorThemeIndex()]},
    paused_{false}{}

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();

  SetUpSounds();
}

void MyApp::SetUpSounds() {
  //Tetris theme song
  ci::audio::SourceFileRef theme_music_file = cinder::audio::load
      (cinder::app::loadAsset("Tetris.mp3"));
  theme_music_ = cinder::audio::Voice::create(theme_music_file);
  theme_music_->start();

  //Line clearing sound effect
  ci::audio::SourceFileRef line_clearing_file = cinder::audio::load
      (cinder::app::loadAsset("line.wav"));
  line_sound_ = cinder::audio::Voice::create(line_clearing_file);

  //Level up sound effect
  ci::audio::SourceFileRef level_up_file = cinder::audio::load
      (cinder::app::loadAsset("clear.wav"));
  clear_sound_ = cinder::audio::Voice::create(level_up_file);

  //Tetromino falling sound effect
  ci::audio::SourceFileRef fall_file = cinder::audio::load
      (cinder::app::loadAsset("fall.wav"));
  fall_sound_ = cinder::audio::Voice::create(fall_file);

  //Game over sound effect
  ci::audio::SourceFileRef game_over_file = cinder::audio::load
      (cinder::app::loadAsset("gameover.wav"));
  game_over_sound_ = cinder::audio::Voice::create(game_over_file);
}

void MyApp::update() {
  if (game_over_) {
    // Fill our vector with the top three scores in our leaderboard
    if (top_players_.empty()) {
      leaderboard_.AddScoreToLeaderBoard({username_, engine_.GetScore()});
      top_players_ = leaderboard_.RetrieveHighScores(kScoreLimit);

      // Make sure that our top scores is not empty
      assert(!top_players_.empty());
    }

    // Stop the theme music when the game ends
    theme_music_->stop();
    return;
  }

  //If the game is paused, don't step the engine
  if (paused_) {
    return;
  }

  //Replay the music if it ends
  if (!theme_music_->isPlaying()) {
    theme_music_->start();
  }

  //Update our score tracker with the engine's score
  if (score_ != engine_.GetScore()) {
    score_ = engine_.GetScore();
    line_sound_->start();
  }

  //Increase the speed if we're above the speed threshold and our score has
  //increased a sufficient amount. This is like each 'level' in Tetris.
  if (speed_ > kSpeedLimit) {
    if (score_ != 0 && score_ % kLevel == 0) {
      speed_ -= kSpeedDecrement;
      clear_sound_->start();
    }
  }


  const auto time = std::chrono::system_clock::now();

  //If enough time has passed (speed), update our game.
  if (time - last_time_ > std::chrono::milliseconds(speed_)) {
    engine_.Step();
    last_time_ = time;
  }

}

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();

  //If the game has ended, draw the end screen.
  if (engine_.IsGameOver() && game_over_) {
    if (!printed_game_over_) {
      cinder::gl::clear(cinder::Color(1, 0, 0));
    }

    DrawGameOver();
    return;
  } else if (engine_.IsGameOver() && !game_over_) {
    //The game has just ended. Draw the regular game screen one more time
    //to show the player that they lost. Next time around, we'll draw the
    //end screen. Without this buffer, it may look to the player that the
    //game ended early.
    game_over_ = true;
  }

  //If the game is paused, there's nothing new to draw
  if (paused_) {
    return;
  }

  //Redraw the screen with a new updated frame
  cinder::gl::clear(cinder::Color(1, 1, 1));
  DrawTetromino();
  DrawProjection();
  DrawScreen();
  DrawScore();
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_k:
    case KeyEvent::KEY_w: {
      engine_.UpdateMovement(tetris::Movement::kRotate);
      break;
    }

    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_j:
    case KeyEvent::KEY_s: {
      engine_.UpdateMovement(tetris::Movement::kDown);
      break;
    }

    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_h:
    case KeyEvent::KEY_a: {
      engine_.UpdateMovement(tetris::Movement::kLeft);
      break;
    }

    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_l:
    case KeyEvent::KEY_d: {
      engine_.UpdateMovement(tetris::Movement::kRight);
      break;
    }

    case KeyEvent::KEY_SPACE: {
      engine_.UpdateMovement(tetris::Movement::kFall);
      fall_sound_->start();
      break;
    }

    case KeyEvent::KEY_p: {
      //Stop or start the music depending on if the user is pausing or unpausing
      if (!paused_) {
        theme_music_->pause();
      } else {
        theme_music_->start();
      }

      paused_ = !paused_;
      break;
    }

    case KeyEvent::KEY_r:
      engine_.Reset();
      break;
  }
}

void MyApp::DrawTetromino() {
  tetris::Tetromino tetromino = engine_.GetTetromino();

  //Loop through each pixel and draw it in our app
  for (int i = 0; i < tetris::kPixelsInTetromino; i++) {
    tetris::Location loc = tetromino.GetPixelLocation(i);
    cinder::gl::color(tetromino.GetColor());

    //If this location is above the screen, don't draw it
    if (loc.Col() < 0) {
      continue;
    }

    cinder::Rectf pixel(loc.Row() * tile_size_,
                  loc.Col() * tile_size_,
                  (loc.Row() * tile_size_) + tile_size_,
                  (loc.Col() * tile_size_) + tile_size_);
    cinder::gl::drawSolidRect(pixel);

    //Draw the outline around each pixel
    cinder::gl::color(outline_color_);
    cinder::gl::drawStrokedRect(pixel, kOutlineLineWidth);
  }
}

void MyApp::DrawProjection() {
  tetris::Tetromino projection_tetromino = engine_.GetProjection();

  //Loop through each pixel and draw its outline in black
  for (int i = 0; i < tetris::kPixelsInTetromino; i++) {
    tetris::Location loc = projection_tetromino.GetPixelLocation(i);
    cinder::gl::color(0, 0, 0);

    //If this location is above the screen, don't draw it
    if (loc.Col() < 0) {
      continue;
    }

    cinder::Rectf pixel(loc.Row() * tile_size_,
                        loc.Col() * tile_size_,
                        (loc.Row() * tile_size_) + tile_size_,
                        (loc.Col() * tile_size_) + tile_size_);
    cinder::gl::drawStrokedRect(pixel);
  }
}

void MyApp::DrawScreen() {
  //Credit for syntax for looping through a 2D vector:
  //https://stackoverflow.com/questions/1784573/iterator-for-2d-vector?rq=1
  //Answered by Austin Hyde
  std::vector<std::vector<cinder::Color>> screen = engine_.GetScreen();
  std::vector< std::vector<cinder::Color> >::const_iterator row;
  std::vector<cinder::Color>::const_iterator col;
  size_t x_index = 0;
  size_t y_index = 0;

  for (row = screen.begin(); row != screen.end(); ++row) {
    for (col = row->begin(); col != row->end(); ++col) {

      //Color the non-white elements in the 2D vector > those are the the pixels
      //that have already touched a surface
      if (*col != cinder::Color(1,1,1)) {
        cinder::gl::color(*col);

        //Draws the pixel
        cinder::Rectf pixel
        (cinder::Rectf(x_index * tile_size_,y_index * tile_size_,
            (x_index * tile_size_) + tile_size_,
            (y_index * tile_size_) + tile_size_));
        cinder::gl::drawSolidRect(pixel);

        //Draw the pixel's outline
        cinder::gl::color(outline_color_);
        cinder::gl::drawStrokedRect(pixel, kOutlineLineWidth);
      }

      x_index++;
    }

    y_index++;
    x_index = 0;
  }
}

void MyApp::DrawScore(){
  //Use the score variable to get the current score of the player.
  const std::string score_text = std::to_string(score_);

  //Make the text blue
  const cinder::Color color = {0, 0, 1};

  //We want our score text to be across the top of the screen
  const cinder::ivec2 size = {FLAGS_tilesize * kWidth, FLAGS_tilesize};

  //We want the score to be in the upper left corner of the screen
  const cinder::vec2 loc =
      {FLAGS_tilesize, FLAGS_tilesize};

  PrintText(score_text, color, size, loc);
}

template <typename C>
void MyApp::PrintText(const std::string& text, const C& color,
    const cinder::ivec2& size, const cinder::vec2& loc) {
  cinder::gl::color(color);

  //Make our text box with the given parameters and draw it onto the screen.
  auto box = cinder::TextBox()
      .alignment(cinder::TextBox::CENTER)
      .font(cinder::Font(kNormalFont, 30))
      .size(size)
      .color(color)
      .backgroundColor(cinder::ColorA
      (0, 0, 0, 0))
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp =
      {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::DrawGameOver() {
  //If we've already printed once, there's no need to keep printing.
  //Allows for lazy printing.
  if (printed_game_over_) return;
  if (top_players_.empty()) return;

  //We're playing the game over sound here because we only want it to play once
  game_over_sound_->start();

  //Get the location, size, and color of our text
  const cinder::vec2 center = {getWindowCenter().x, FLAGS_tilesize};
  const cinder::ivec2 size = {500, FLAGS_tilesize};
  const cinder::Color color = cinder::Color::white();

  size_t row = 1;
  PrintText("Game Over", color, size, center);

  //Print the top 3 scores, one row below another
  PrintText("Leaderboard", color, size,
      {center.x, center.y + (++row) * FLAGS_tilesize});
  for (const tetris::Player& player : top_players_) {
    std::stringstream ss;
    ss << player.name << ": " << player.score;
    PrintText(ss.str(), color, size,
        {center.x, center.y + (++row) * FLAGS_tilesize});
  }

  //Create a space before printing the next score
  row++;

  //Print the player's most recent score
  PrintText("Your Score", color, size,
      {center.x, center.y + (++row) * FLAGS_tilesize});
  PrintText(std::to_string(engine_.GetScore()), color, size,
      {center.x, center.y + (++row) * FLAGS_tilesize});

  printed_game_over_ = true;
}

}  // namespace tetrisapp
