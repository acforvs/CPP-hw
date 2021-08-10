#include "Rectangle.hpp"
#include <cstdio>

Rectangle::Rectangle(int id, int x, int y, int width, int height)
    : Figure(id, x, y) {
  width_ = width;
  height_ = height;
}

Rectangle::~Rectangle() {}

void Rectangle::print() const {
  printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id_, x_, y_,
         width_, height_);
}

bool Rectangle::is_inside(int px, int py) const {
  return (x_ - width_ / 2 <= px && px <= x_ + width_ / 2 &&
          y_ - height_ / 2 <= py && py <= y_ + height_ / 2);
}

void Rectangle::zoom(int factor) {
  width_ *= factor;
  height_ *= factor;
}
