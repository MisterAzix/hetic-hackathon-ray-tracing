//
// Created by Maxence Breuilles on 28/10/2024.
//

#pragma once

#include <iostream>
#include "Color.h"
#include <vector>

class Image {
private:
  unsigned int width = 0;
  unsigned int height = 0;
  std::vector<Color> buffer;
public:
  Image(unsigned int w, unsigned int h);
  Image(unsigned int w, unsigned int h, Color c);
  ~Image();

  void SetPixel(unsigned int x, unsigned int y, Color color);
  Color GetPixel(unsigned int x, unsigned int y);
  void WriteFile(const char* filename);

  unsigned int getWidth() const { return width; }
  unsigned int getHeight() const { return height; }
};