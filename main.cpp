#include <iostream>

#include "ppm.hh"
int main() {
  Ppm image(std::cin);
  std::cout << image.pixels.size();
  return 0;
}