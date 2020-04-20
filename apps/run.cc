// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <gflags/gflags.h>

#include "my_app.h"

using cinder::app::App;
using cinder::app::RendererGl;


namespace myapp {

DEFINE_uint32(tilesize, 30, "the size of each tile");
DEFINE_string(name, "Guest", "the name of the player");

const int kSamples = 8;

void ParseArgs(std::vector<std::string>* args) {
  gflags::SetUsageMessage(
      "Play a game of Tetris. Pass --helpshort for options.");
  int argc = static_cast<int>(args->size());

  std::vector<char*> argvs;
  for (std::string& str : *args) {
    argvs.push_back(&str[0]);
  }

  char** argv = argvs.data();
  gflags::ParseCommandLineFlags(&argc, &argv, true);
}

void SetUp(App::Settings* settings) {
  std::vector<std::string> args = settings->getCommandLineArgs();
  ParseArgs(&args);

  const int width = static_cast<int>(kWidth*FLAGS_tilesize);
  const int height = static_cast<int>(kHeight*FLAGS_tilesize);

  settings->setWindowSize(width, height);
  settings->setResizable(false);
  settings->setTitle("Tetris");
}

}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)
