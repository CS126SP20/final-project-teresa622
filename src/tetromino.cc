//
// Created by Teresa Dong on 4/17/20.
//

#include "mylibrary/tetromino.h"

#include <ctime>

namespace mylibrary {

Tetromino::Tetromino(int center_tile, size_t theme_index) {
  //Generate a random number quickly: 0-6
  //Credit: https://stackoverflow.com/questions/20201141/same-random-numbers-generated-every-time-in-c
  //Answered by rkyser
  struct timespec ts{};
  clock_gettime(CLOCK_MONOTONIC, &ts);

  /* using nano-seconds instead of seconds */
  srand((time_t)ts.tv_nsec);
  int random_num = rand() % kNumTetrominoTypes;
  tetromino_type_ = kTetrominoTypes[random_num];
  color_ = kThemes[theme_index][random_num];
  InitializePixels(center_tile);
}

Tetromino::Tetromino(int center_tile, TetrominoType tetromino_type) {
  tetromino_type_ = tetromino_type;
  InitializePixels(center_tile);
}

void Tetromino::InitializePixels(int center_tile) {
  switch (tetromino_type_) {
    case TetrominoType::kZ:
      GenerateZ(center_tile);
      break;
    case TetrominoType::kS:
      GenerateS(center_tile);
      break;
    case TetrominoType::kT:
      GenerateT(center_tile);
      break;
    case TetrominoType::kO:
      GenerateO(center_tile);
      break;
    case TetrominoType::kL:
      GenerateL(center_tile);
      break;
    case TetrominoType::kJ:
      GenerateJ(center_tile);
      break;
    case TetrominoType::kI:
      GenerateI(center_tile);
      break;
  }
}

//Each different type of tetromino generated given the center_tile
void Tetromino::GenerateZ(int center_tile) {
  pixels[0] = {center_tile + 1, 1};
  pixels[1] = {center_tile, 1};
  pixels[2] = {center_tile, 0};
  pixels[3] = {center_tile - 1, 0};
}

void Tetromino::GenerateS(int center_tile) {
  pixels[0] = {center_tile - 1, 1};
  pixels[1] = {center_tile, 1};
  pixels[2] = {center_tile, 0};
  pixels[3] = {center_tile + 1, 0};
}

void Tetromino::GenerateT(int center_tile) {
  pixels[0] = {center_tile - 1, 1};
  pixels[1] = {center_tile, 1};
  pixels[2] = {center_tile + 1, 1};
  pixels[3] = {center_tile, 0};
}

void Tetromino::GenerateO(int center_tile) {
  pixels[0] = Location(center_tile - 1, 0);
  pixels[1] = Location(center_tile, 0);
  pixels[2] = Location(center_tile - 1, 1);
  pixels[3] = Location(center_tile, 1);
}

void Tetromino::GenerateI(int center_tile) {
  pixels[0] = Location(center_tile - 2, 1);
  pixels[1] = Location(center_tile - 1, 1);
  pixels[2] = Location(center_tile, 1);
  pixels[3] = Location(center_tile + 1, 1);
}

void Tetromino::GenerateJ(int center_tile) {
  pixels[0] = Location(center_tile, 0);
  pixels[1] = Location(center_tile, 1);
  pixels[2] = Location(center_tile, 2);
  pixels[3] = Location(center_tile - 1, 2);
}

void Tetromino::GenerateL(int center_tile) {
  pixels[0] = Location(center_tile, 0);
  pixels[1] = Location(center_tile, 1);
  pixels[2] = Location(center_tile, 2);
  pixels[3] = Location(center_tile + 1, 2);
}

void Tetromino::MoveTetromino(int horizontal_amount, int vertical_amount) {
  //Loop through each pixel and moves it with the given amount
  for (auto& pixel : pixels) {
    pixel = Location(pixel.Row() + horizontal_amount,
        pixel.Col() + vertical_amount);
  }
}

void Tetromino::RotateTetromino() {
  //If the tetromino is type O, then rotation does nothing
  if (tetromino_type_ == TetrominoType::kO) {
    return;
  }

  //Get the points of rotation from which each pixel will rotate around
  int rotation_point_x = pixels[kRotationPointIndex].Row();
  int rotation_point_y = pixels[kRotationPointIndex].Col();

  //Rotate each pixel
  for (auto& pixel : pixels) {
    pixel = Location((rotation_point_x + rotation_point_y) - pixel.Col(),
                     (rotation_point_y - rotation_point_x) + pixel.Row());
  }
}

//Tetromino getters
Location Tetromino::GetRotationPoint() {
  return pixels[kRotationPointIndex];
}

TetrominoType Tetromino::GetTetrominoType() {
  return tetromino_type_;
}

Location Tetromino::GetPixelLocation(size_t index) {
  return pixels[index];
}

cinder::Color Tetromino::GetColor() {
  return color_;
}

}