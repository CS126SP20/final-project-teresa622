//
// Created by Teresa Dong on 4/17/20.
//

#ifndef FINALPROJECT_SRC_LEADERBOARD_H_
#define FINALPROJECT_SRC_LEADERBOARD_H_

#include <sqlite_modern_cpp.h>

#include "player.h"

namespace tetris {

class LeaderBoard {
 public:

  /**
   * Creates a new leaderboard table if it doesn't already exist.
   * @param db_path the path to access the database
   */
  explicit LeaderBoard(const std::string& db_path);

  /**
   * Adds a player to the leaderboard
   */
  void AddScoreToLeaderBoard(const Player&);

  /**
   * Returns a list of the players with the highest scores, in decreasing order.
   * @param limit the size of our list (the number of high scores we're
   * retrieving
   * @return the list of top scores
   */
  std::vector<Player> RetrieveHighScores(size_t limit);

 private:
  sqlite::database db_;
};

}  // namespace mylibrary
#endif  // FINALPROJECT_SRC_LEADERBOARD_H_
