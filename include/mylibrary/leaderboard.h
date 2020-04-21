//
// Created by Teresa Dong on 4/17/20.
//

#ifndef FINALPROJECT_SRC_LEADERBOARD_H_
#define FINALPROJECT_SRC_LEADERBOARD_H_

#include <sqlite_modern_cpp.h>

#include "player.h"

namespace mylibrary {

class LeaderBoard {
 public:
  // Creates a new leaderboard table if it doesn't already exist.
  explicit LeaderBoard(const std::string& db_path);

  // Adds a player to the leaderboard.
  void AddScoreToLeaderBoard(const Player&);

  // Returns a list of the players with the highest scores, in decreasing order.
  // The size of the list should be no greater than `limit`.
  std::vector<Player> RetrieveHighScores(const size_t limit);

  // Returns a list of the players with the highest scores, in decreasing order,
  // that have the same `name` as the input player name.
  // The size of the list should be no greater than `limit`.
  std::vector<Player> RetrieveHighScores(const Player&, const size_t limit);
 private:
  sqlite::database db_;
};

}  // namespace mylibrary
#endif  // FINALPROJECT_SRC_LEADERBOARD_H_
