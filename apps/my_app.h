// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/leaderboard.h>
#include <mylibrary/tetromino.h>

#include "mylibrary/engine.h"

namespace myapp {

const int kTileSize = 50;
const int kSize = 16;

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  void DrawTetromino();
  void DrawScreen();

 private:
  std::chrono::time_point<std::chrono::system_clock> last_time_;
  mylibrary::Engine engine_;
  mylibrary::LeaderBoard leaderboard_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
