//
// Created by Teresa Dong on 4/17/20.
//

#include "mylibrary/leaderboard.h"
#include <string>

namespace mylibrary {
LeaderBoard::LeaderBoard(const std::string& db_path) : db_{db_path} {
  db_ << "CREATE TABLE if not exists leaderboard (\n"
         "  name  TEXT NOT NULL,\n"
         "  score INTEGER NOT NULL\n"
         ");";
}
}
