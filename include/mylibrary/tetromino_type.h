//
// Created by Teresa Dong on 4/17/20.
//

#ifndef FINALPROJECT_SRC_TETROMINO_TYPE_H_
#define FINALPROJECT_SRC_TETROMINO_TYPE_H_
namespace mylibrary {

//All the types of tetrominoes that exist
enum class TetrominoType { kO, kL, kS, kZ, kI, kJ, kT };

//Note: These are just rough sketches to give an idea of what the tetrominoes
//look like. They are not to scale.
/*
 * kO is the square:
 *   ___________
 *  |     |     |
 *  |_____|_____|
 *  |     |     |
 *  |_____|_____|
 */

/*
 * kL:
 *  _____
 * |     |
 * |     |
 * |     |____
 * |          |
 * |__________|
 */

/*
 * kS:
 *         _________
 *        |         |
 *  ______|    _____|
 * |          |
 * |__________|
 *
 */

/*
 * kZ:
 *  __________
 * |          |
 * |_____     |_______
 *       |            |
 *       |____________|
 */

/*
 * kI:
 *  _____
 * |     |
 * |     |
 * |     |
 * |     |
 * |     |
 * |_____|
 */

/*
 * kJ:
 *        _____
 *       |     |
 *       |     |
 *   ____|     |
 *  |          |
 *  |__________|
 */

/*
 * kT:
 *        _______
 *       |       |
 *  _____|       |_____
 * |                   |
 * |___________________|
 */

}   // namespace mylibrary

#endif  // FINALPROJECT_SRC_TETROMINO_TYPE_H_
