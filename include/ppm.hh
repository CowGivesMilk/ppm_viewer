#ifndef PPM_H
#define PPM_H

#include "pixel.hh"
#include <QImage>
#include <cstddef>
#include <istream>
#include <vector>
struct Ppm {
public:
  std::size_t width, height;
  unsigned char max_value;
  std::vector<Pixel> pixels;
  Ppm(std::istream &input);
  QImage image();
};

#endif