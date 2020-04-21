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

const char kDbPath[] = "tetris.db";

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
    //750 ms is the starting speed of the tetrominoes dropping
    speed_{750} {}

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
}

void MyApp::update() {
  const auto time = std::chrono::system_clock::now();
  if (time - last_time_ > std::chrono::milliseconds(speed_)) {
    engine_.Step();
    last_time_ = time;
  }

}

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();

  if (engine_.IsGameOver() && game_over) {
    if (!printed_game_over_) cinder::gl::clear(cinder::Color(1, 0, 0));
    DrawGameOver();
    return;
  } else if (engine_.IsGameOver() && !game_over) {
    game_over = true;
  }

  cinder::gl::clear();
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
    cinder::gl::color(0, 1, 0);

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
  std::vector<std::vector<bool>> screen = engine_.GetScreen();
  std::vector< std::vector<bool> >::const_iterator row;
  std::vector<bool>::const_iterator col;
  size_t x_index = 0;
  size_t y_index = 0;

  for (row = screen.begin(); row != screen.end(); ++row) {
    for (col = row->begin(); col != row->end(); ++col) {
      //Color the true locations in the 2D vector > those are the the pixels
      //that have already touched a surface
      if (*col) {
        cinder::gl::color(0, 1, 0);
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
void PrintText(const std::string& text, const C& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = cinder::TextBox()
      .alignment(cinder::TextBox::CENTER)
      .font(cinder::Font(kNormalFont, 30))
      .size(size)
      .color(color)
      .backgroundColor(cinder::ColorA(0, 0, 0, 0))
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::DrawGameOver() {
  if (printed_game_over_) return;
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {200, 50};
  const cinder::Color color = cinder::Color::white();

  PrintText("Game Over :(", color, size, center);
  printed_game_over_ = true;
}

}  // namespace myapp
