#include "ppm.hh"

#include <iostream>
#include <stdexcept>
#include <string>

Ppm::Ppm(std::istream& input) {
  std::string magic;

  input >> magic;

  if (magic != "P3") {
    throw std::runtime_error("Expected P3 PPM");
  }

  input >> width >> height;

  int max;
  input >> max;

  if (max < 1 || max > 255) {
    throw std::runtime_error("Invalid maximum color value");
  }

  max_value = static_cast<unsigned char>(max);

  pixels.reserve(width * height);

  for (std::size_t i = 0; i < width * height; ++i) {
    int r, g, b;

    if (!(input >> r >> g >> b)) {
      throw std::runtime_error("Unexpected end of PPM data");
    }

    if (r < 0 || r > max || g < 0 || g > max || b < 0 || b > max) {
      throw std::runtime_error("Invalid pixel value");
    }

    pixels.emplace_back(static_cast<unsigned char>(r),
                        static_cast<unsigned char>(g),
                        static_cast<unsigned char>(b));
  }
}