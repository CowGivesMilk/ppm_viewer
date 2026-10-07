#ifndef PPM_H
#define PPM_H

#include <cstddef>
#include <istream>
#include <vector>

#include "pixel.hh"
struct Ppm {
 public:
  std::size_t width, height;
  unsigned char max_value;
  std::vector<Pixel> pixels;
  Ppm(std::istream& input);
};

#endif