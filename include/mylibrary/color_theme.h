//
// Created by Teresa Dong on 4/22/20.
//

#ifndef FINALPROJECT_SRC_COLOR_THEME_H_
#define FINALPROJECT_SRC_COLOR_THEME_H_

#include <cinder/Color.h>

namespace mylibrary {

const size_t kNumOfThemes = 6;
const cinder::Color kThemes[kNumOfThemes][7] =
    {{cinder::Color::hex(0x464e34),
      cinder::Color::hex(0x778457),
      cinder::Color::hex(0xb3c18f),
      cinder::Color::hex(0x959b87),
      cinder::Color::hex(0x80705b),
      cinder::Color::hex(0x574834),
      cinder::Color::hex(0x2f2415)},

     {cinder::Color::hex(0x151b23),
      cinder::Color::hex(0x801e3a),
      cinder::Color::hex(0xc46277),
      cinder::Color::hex(0x694650),
      cinder::Color::hex(0x5c114a),
      cinder::Color::hex(0xa37688),
      cinder::Color::hex(0x3d4563)},

     {cinder::Color::hex(0x4B88AE),
      cinder::Color::hex(0x92DBEC),
      cinder::Color::hex(0x87B8D6),
      cinder::Color::hex(0x807891),
      cinder::Color::hex(0xcf8095),
      cinder::Color::hex(0xef9c8f),
      cinder::Color::hex(0xffd3ca)},

     {cinder::Color::hex(0xc3268a),
      cinder::Color::hex(0xc13ace),
      cinder::Color::hex(0x6d4fd8),
      cinder::Color::hex(0x68e4aa),
      cinder::Color::hex(0xa1f798),
      cinder::Color::hex(0xe0cb6e),
      cinder::Color::hex(0xf4727d)},

     {cinder::Color::hex(0xf4c5d5),
      cinder::Color::hex(0xb7a8bf),
      cinder::Color::hex(0x919bd1),
      cinder::Color::hex(0xa48fae),
      cinder::Color::hex(0x7c7b9b),
      cinder::Color::hex(0x535480),
      cinder::Color::hex(0x4e3968)},

     {cinder::Color::hex(0x023536),
      cinder::Color::hex(0x02555e),
      cinder::Color::hex(0x0f7372),
      cinder::Color::hex(0x1a9d9b),
      cinder::Color::hex(0x608585),
      cinder::Color::hex(0xadc8c8),
      cinder::Color::hex(0x95ebea)}};

const cinder::Color kThemeOutline[kNumOfThemes] =
    {cinder::Color::hex(0xfedee1),
     cinder::Color(1, 1, 1),
     cinder::Color(0, 0, 0),
     cinder::Color(0, 0, 0),
     cinder::Color(1, 1, 1),
     cinder::Color::hex(0xfebdae)};

}
#endif  // FINALPROJECT_SRC_COLOR_THEME_H_
