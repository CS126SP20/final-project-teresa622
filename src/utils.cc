//
// Created by Teresa Dong on 5/2/20.
//

#include "mylibrary/utils.h"

namespace utils {

size_t utils::RandNumInRange(size_t end) {
  //Generate a random number quickly
  //Credit: https://stackoverflow.com/questions/20201141/same-random-numbers-generated-every-time-in-c
  //(^ url cannot be less than 80 characters)
  //Answered by rkyser
  struct timespec ts{};
  clock_gettime(CLOCK_MONOTONIC, &ts);

  /* using nano-seconds instead of seconds */
  srand((time_t)ts.tv_nsec);

  return rand() % end;
}

}   // namespace utils