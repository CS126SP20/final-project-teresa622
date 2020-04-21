// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>

#include "mylibrary/leaderboard.h"
#include "mylibrary/tetromino.h"
#include "mylibrary/engine.h"

namespace myapp {
const size_t kWidth = 12;
const size_t kHeight = 15;

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
  size_t tile_size_;
  std::string username_;
  size_t speed_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
