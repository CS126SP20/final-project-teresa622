//
// Created by Teresa Dong on 5/2/20.
//

#ifndef FINALPROJECT_SRC_UTILS_H_
#define FINALPROJECT_SRC_UTILS_H_

#include <string>

namespace utils {

/**
 * Returns a random number from 0 to the specified range
 * @param range non-inclusive max: numbers will be generated from 0 to range - 1
 * @return the randomly generated number from the range
 */
size_t RandNumInRange(size_t range);

}   //  namespace utils
#endif  // FINALPROJECT_SRC_UTILS_H_
