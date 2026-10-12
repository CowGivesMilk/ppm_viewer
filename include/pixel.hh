#ifndef PIXEL_H
#define PIXEL_H
#include <QColor>
class Pixel {
public:
  unsigned char red, green, blue;
  Pixel(unsigned char r, unsigned char g, unsigned char b);
  QColor color();
};
#endif