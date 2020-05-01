//
// Created by Teresa Dong on 4/21/20.
//

#ifndef FINALPROJECT_SRC_PLAYER_H_
#define FINALPROJECT_SRC_PLAYER_H_
#include <string>

namespace tetris {

//Stores each player's name and score. Used for score keeping in the database.
struct Player {
  Player(const std::string& name, size_t score) : name(name), score(score) {}
  std::string name;
  size_t score;
};

}  // namespace mylibrary

#endif  // FINALPROJECT_SRC_PLAYER_H_
