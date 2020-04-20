// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <gflags/gflags.h>

#include "mylibrary/engine.h"

namespace myapp {

const char kDbPath[] = "tetris.db";

DECLARE_uint32(tilesize);
DECLARE_string(name);

using cinder::app::KeyEvent;
MyApp::MyApp()
  : engine_{kWidth, kHeight},
    leaderboard_{cinder::app::getAssetPath(kDbPath).string()},
    tile_size_{FLAGS_tilesize},
    username_{FLAGS_name},
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
    draw();
  }

}

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();
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

  }
}

void MyApp::DrawTetromino() {
  mylibrary::Tetromino tetromino = engine_.GetTetromino();

  //Loop through each pixel and draw it in our app
  for (int i = 0; i < 4; i++) {
    mylibrary::Location loc = tetromino.GetPixelLocation(i);
    cinder::gl::color(0, 1, 0);
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

}  // namespace myapp
