#include <iostream>

#include "ppm.hh"
int main() {
  Ppm image(std::cin);
  image.display();
  return 0;
}