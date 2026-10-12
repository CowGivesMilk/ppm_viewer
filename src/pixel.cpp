#include "pixel.hh"
#include <QColor>
#include <qcolor.h>
Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b)
    : red(r), green(g), blue(b) {}
QColor Pixel::color() {
  return QColor::fromRgb(this->red, this->green, this->blue);
}