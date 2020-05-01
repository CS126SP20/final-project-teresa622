//
// Created by Teresa Dong on 4/17/20.
//

#include "mylibrary/leaderboard.h"

#include <string>

#include "mylibrary/player.h"

namespace tetris {

LeaderBoard::LeaderBoard(const std::string& db_path) : db_{db_path} {
  db_ << "CREATE TABLE if not exists leaderboard (\n"
         "  name  TEXT NOT NULL,\n"
         "  score INTEGER NOT NULL\n"
         ");";
}

void LeaderBoard::AddScoreToLeaderBoard(const Player& player) {
  db_ << u"insert into leaderboard (name,score) values (?,?);"
      << player.name
      << player.score;
}

std::vector<Player> GetPlayers(sqlite::database_binder* rows) {
  std::vector<Player> players;

  for (auto&& row : *rows) {
    std::string name;
    size_t score;
    row >> name >> score;
    Player player = {name, score};
    players.push_back(player);
  }

  return players;
}

std::vector<Player> LeaderBoard::RetrieveHighScores(const size_t limit) {
  try {
    auto rows = db_<< "SELECT name,score FROM "
                      "leaderboard ORDER BY score DESC LIMIT (?);"
                   << limit;

    return GetPlayers(&rows);
  } catch (const std::exception& e) {
    std::cerr << "Query error at retrieve universal high scores";
  }
}

}
