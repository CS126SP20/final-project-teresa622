// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <mylibrary/engine.h>

namespace myapp {

using cinder::app::KeyEvent;
MyApp::MyApp() : engine_{kSize, kSize} {
}

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
}

void MyApp::update() {
  const auto time = std::chrono::system_clock::now();
  if (time - last_time_ > std::chrono::milliseconds(200)) {
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

void MyApp::keyDown(KeyEvent event) { }

void MyApp::DrawTetromino() {
  mylibrary::Tetromino tetromino = engine_.GetTetromino();

  //Loop through each pixel and draw it in our app
  for (int i = 0; i < 4; i++) {
    mylibrary::Location loc = tetromino.GetPixelLocation(i);
    cinder::gl::color(0, 1, 0);
    cinder::gl::drawSolidRect(cinder::Rectf(loc.Row() * kTileSize,
        loc.Col() * kTileSize, (loc.Row() * kTileSize) + kTileSize,
        (loc.Col() * kTileSize) + kTileSize));
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
        cinder::gl::drawSolidRect(cinder::Rectf(x_index * kTileSize,
            y_index * kTileSize,(x_index * kTileSize) + kTileSize,
            (y_index * kTileSize) + kTileSize));
      }
      x_index++;
    }
    y_index++;
    x_index = 0;
  }
}

}  // namespace myapp
