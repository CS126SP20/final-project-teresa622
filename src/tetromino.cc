//
// Created by Teresa Dong on 4/17/20.
//

#include "mylibrary/tetromino.h"

#include <ctime>

namespace mylibrary {

Tetromino::Tetromino(int center_tile) {
  //Generate a random number quickly: 0-6
  //Credit: https://stackoverflow.com/questions/20201141/same-random-numbers-generated-every-time-in-c
  //Answered by rkyser
  struct timespec ts{};
  clock_gettime(CLOCK_MONOTONIC, &ts);

  /* using nano-seconds instead of seconds */
  srand((time_t)ts.tv_nsec);
  tetromino_type_ = kTetrominoTypes[rand() % kNumTetrominoTypes];
  InitializePixels_(center_tile);
}

Tetromino::Tetromino(int center_tile, TetrominoType tetromino_type) {
  tetromino_type_ = tetromino_type;
  InitializePixels_(center_tile);
  FindContactPixels();
}

void Tetromino::InitializePixels_(int center_tile) {
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
  pixels[0] = {center_tile - 1, 0};
  pixels[1] = {center_tile, 0};
  pixels[2] = {center_tile + 1, 0};
  pixels[3] = {center_tile, 1};
}

void Tetromino::GenerateO(int center_tile) {
  pixels[0] = Location(center_tile - 1, 0);
  pixels[1] = Location(center_tile, 0);
  pixels[2] = Location(center_tile - 1, 1);
  pixels[3] = Location(center_tile, 1);
}

void Tetromino::GenerateI(int center_tile) {
  pixels[0] = Location(center_tile, 0);
  pixels[1] = Location(center_tile, 1);
  pixels[2] = Location(center_tile, 2);
  pixels[3] = Location(center_tile, 3);
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

Location Tetromino::GetPixelLocation(size_t index) {
  return pixels[index];
}

void Tetromino::MoveTetromino(int horizontal_amount, int vertical_amount) {
  for (auto& pixel : pixels) {
    pixel = Location(pixel.Row() + horizontal_amount,
        pixel.Col() + vertical_amount);
  }
}

void Tetromino::RotateTetromino(int width, int height) {
  int rotation_point_x = pixels[rotation_point_index].Row();
  int rotation_point_y = pixels[rotation_point_index].Col();

  //Rotate each pixel
  for (auto& pixel : pixels) {
    pixel = Location((rotation_point_x + rotation_point_y) - pixel.Col(),
                     (rotation_point_y - rotation_point_x) + pixel.Row());
  }

  rotated = true;
}

Location Tetromino::GetRotationLocation() {
  return pixels[rotation_point_index];
}

TetrominoType Tetromino::GetTetrominoType() {
  return tetromino_type_;
}

std::vector<int> Tetromino::FindContactPixels() {
  //If tetromino is not rotated, there is no need
  //to recalculate the contact indexes
  if (!rotated) {
    return contact_pixel_indexes;
  }

  //The tetromino was rotated. Clear our current contact indexes and recalculate
  contact_pixel_indexes.clear();
  std::vector<int> checked_indexes;

  for (int i = 0; i < kPixelsInTetromino; i++) {
    //Check if we have already evaluates this pixel
    if (std::find(checked_indexes.begin(), checked_indexes.end(), i)
    != checked_indexes.end()) {
      continue;
    }

    //Else add it to our checked indexes
    checked_indexes.push_back(i);
    Location contact_pixel = pixels[i];
    size_t pixel_index = i;

    //Loop through the pixels and determine if this is the lowest pixel
    //in this column
    for (int j = i; j < kPixelsInTetromino; j++) {
      if (pixels[j].Row() == contact_pixel.Row()) {

        //We've checked this pixel now, regardless if it's the contact or not
        checked_indexes.push_back(j);
        if (pixels[j].Col() > contact_pixel.Col()) {
          contact_pixel = pixels[j];
          pixel_index = j;
        }
      }
    }

    //Add this row's contact pixel into our vector
    contact_pixel_indexes.push_back(pixel_index);
  }

  //Reset rotated boolean to avoid recalculation
  rotated = false;
  return contact_pixel_indexes;
}

}