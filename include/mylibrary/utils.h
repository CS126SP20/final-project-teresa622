//
// Created by Teresa Dong on 5/2/20.
//

#ifndef FINALPROJECT_SRC_UTILS_H_
#define FINALPROJECT_SRC_UTILS_H_

#include <string>

namespace utils {

/**
 * Returns a random number from 0 to the specified end
 * @param end non-inclusive max: numbers will be generated from 0 to end - 1
 * @return the randomly generated number from the end
 */
size_t RandNumInRange(size_t end);

}   //  namespace utils
#endif  // FINALPROJECT_SRC_UTILS_H_
