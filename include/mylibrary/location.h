//
// Created by Teresa Dong on 4/17/20.
//

#ifndef FINALPROJECT_SRC_LOCATION_H_
#define FINALPROJECT_SRC_LOCATION_H_

#include <ostream>

namespace tetris {

//This class was inspired by the Snake Project Assignment from CS126.
// Represents a location on the game screen.
class Location {
 public:
  /**
   * Location constructor that stores a row and column location
   * @param row the row location of this Location object
   * @param col the column location of this Location object
   */
  Location(int row, int col);

  /**
   * Compares two Locations. If they have the same column and row, they are
   * equal.
   * @param rhs the other Location that this Location is being compared to
   * @return whether or not the two Locations are equal
   */
  bool operator==(const Location& rhs) const;

  // Accessors
  int Row() const;
  int Col() const;

 private:
  //Stores the row and column of this Location
  int row_;
  int col_;
};

}  // namespace tetris

#endif  // FINALPROJECT_SRC_LOCATION_H_
