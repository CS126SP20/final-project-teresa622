// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <gflags/gflags.h>
#include <cinder/Text.h>
#include <cinder/Font.h>

#include "my_app.h"
#include "mylibrary/engine.h"

namespace myapp {

//Used to find the path to access our scoring database
const char kDbPath[] = "tetris.db";

//The number of top scores to display in the game over screen
const int kScoreLimit = 3;

//750 ms is the starting speed of how fast the game updates and how fast the
//tetrominoes drop
const int kStartSpeed = 750;

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

DECLARE_uint32(tilesize);
DECLARE_string(name);

using cinder::app::KeyEvent;

MyApp::MyApp()
  : engine_{kWidth, kHeight},
    leaderboard_{cinder::app::getAssetPath(kDbPath).string()},
    tile_size_{FLAGS_tilesize},
    username_{FLAGS_name},
    speed_{kStartSpeed} {}

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
}

void MyApp::update() {
  if (game_over) {

    //Fill our vector with the top three scores in our leaderboard
    if (top_players_.empty()) {
      leaderboard_.AddScoreToLeaderBoard({username_, engine_.GetScore()});
      top_players_ = leaderboard_.RetrieveHighScores(kScoreLimit);

      //Make sure that our top scores is not empty
      assert(!top_players_.empty());
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
  if (engine_.IsGameOver() && game_over) {
    if (!printed_game_over_) {
      cinder::gl::clear(cinder::Color(1, 0, 0));
    }

    DrawGameOver();
    return;
  } else if (engine_.IsGameOver() && !game_over) {
    //The game has just ended. Draw the regular game screen one more time
    //to show the player that they lost. Next time around, we'll draw the
    //end screen. Without this buffer, it may look to the player that the
    //game ended early.
    game_over = true;
  }

  //Redraw the screen with a new updated frame
  cinder::gl::clear(cinder::Color(1, 1, 1));
  DrawTetromino();
  DrawScreen();
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_k:
    case KeyEvent::KEY_w: {
      engine_.UpdateMovement(mylibrary::Movement::kRotate);
      break;
    }

    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_j:
    case KeyEvent::KEY_s: {
      engine_.UpdateMovement(mylibrary::Movement::kDown);
      break;
    }

    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_h:
    case KeyEvent::KEY_a: {
      engine_.UpdateMovement(mylibrary::Movement::kLeft);
      break;
    }

    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_l:
    case KeyEvent::KEY_d: {
      engine_.UpdateMovement(mylibrary::Movement::kRight);
      break;
    }

    case KeyEvent::KEY_SPACE: {
      engine_.UpdateMovement(mylibrary::Movement::kFall);
      break;
    }

  }
}

void MyApp::DrawTetromino() {
  mylibrary::Tetromino tetromino = engine_.GetTetromino();

  //Loop through each pixel and draw it in our app
  for (int i = 0; i < 4; i++) {
    mylibrary::Location loc = tetromino.GetPixelLocation(i);
    cinder::gl::color(tetromino.GetColor());

    //If this location is above the screen, don't draw it
    if (loc.Col() < 0) {
      continue;
    }

    cinder::gl::drawSolidRect(cinder::Rectf(loc.Row() * tile_size_,
        loc.Col() * tile_size_, (loc.Row() * tile_size_) + tile_size_,
        (loc.Col() * tile_size_) + tile_size_));
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
        //cinder::gl::color(0, 1, 0);
        cinder::gl::drawSolidRect(cinder::Rectf(x_index * tile_size_,
            y_index * tile_size_,(x_index * tile_size_) + tile_size_,
            (y_index * tile_size_) + tile_size_));
      }

      x_index++;
    }

    y_index++;
    x_index = 0;
  }
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

  //Get the location, size, and color of our text
  const cinder::vec2 center = {getWindowCenter().x, 40};
  const cinder::ivec2 size = {200, 50};
  const cinder::Color color = cinder::Color::white();

  size_t row = 1;
  PrintText("Game Over :(", color, size, center);

  //Print the top 3 scores, one row below another
  PrintText("High Scores", color, size,
      {center.x, center.y + (++row) * 50});
  for (const  mylibrary::Player& player : top_players_) {
    std::stringstream ss;
    ss << player.name << ": " << player.score;
    PrintText(ss.str(), color, size,
        {center.x, center.y + (++row) * 50});
  }

  //Create a space before printing the next score
  row++;

  //Print the player's most recent score
  PrintText("Your Score", color, size,
      {center.x, center.y + (++row) * 50});
  PrintText(std::to_string(engine_.GetScore()), color, size,
      {center.x, center.y + (++row) * 50});

  printed_game_over_ = true;
}

}  // namespace myapp
