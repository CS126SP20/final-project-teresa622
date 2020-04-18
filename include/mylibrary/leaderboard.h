//
// Created by Teresa Dong on 4/17/20.
//

#ifndef FINALPROJECT_SRC_LEADERBOARD_H_
#define FINALPROJECT_SRC_LEADERBOARD_H_
#include <sqlite_modern_cpp.h>
namespace mylibrary {

class LeaderBoard {
 public:
  // Creates a new leaderboard table if it doesn't already exist.
  explicit LeaderBoard(const std::string& db_path);

 private:
  sqlite::database db_;
};

}  // namespace mylibrary
#endif  // FINALPROJECT_SRC_LEADERBOARD_H_
