//
// Created by Teresa Dong on 4/17/20.
//

#ifndef FINALPROJECT_SRC_LOCATION_H_
#define FINALPROJECT_SRC_LOCATION_H_

#include <ostream>

namespace tetris {

//This class was inspired by the Snake Project Assignment from CS126.
// Represents a location on the board.
class Location {
 public:
  Location(int row, int col);

  // Comparison operators.
  bool operator==(const Location& rhs) const;

  // Accessors.
  int Row() const;
  int Col() const;

 private:
  int row_;
  int col_;
};

}  // namespace tetris

#endif  // FINALPROJECT_SRC_LOCATION_H_
