// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <mylibrary/engine.h>

namespace myapp {

using cinder::app::KeyEvent;
MyApp::MyApp() : tetromino(8), engine_{16, 16} {
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
  mylibrary::Tetromino tetromino1 = engine_.GetTetromino();
  for (int i = 0; i < 4; i++) {
    mylibrary::Location loc = tetromino1.GetPixelLocation(i);
    cinder::gl::color(0, 1, 0);
    cinder::gl::drawSolidRect(cinder::Rectf(loc.Row()*50, loc.Col()*50, (loc.Row()*50) + 50, (loc.Col()*50) + 50));
  }
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
