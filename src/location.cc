//
// Created by Teresa Dong on 4/17/20.
//

#include "mylibrary/location.h"

namespace tetris {

Location::Location(int row, int col) : row_(row), col_(col) {}

bool Location::operator==(const Location& rhs) const {
  return row_ == rhs.row_ && col_ == rhs.col_;
}

int Location::Row() const { return row_; }

int Location::Col() const { return col_; }

}  // namespace tetris