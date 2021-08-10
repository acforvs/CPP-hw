#include "Circle.hpp"
#include <cstdio>
#include <cstring>

Circle::Circle(int id, int x, int y, int radius, const char *label)
    : Figure(id, x, y) {
  radius_ = radius;
  label_ = new char[strlen(label) + 1];
  strcpy(label_, label);
}

Circle::~Circle() { delete[] label_; }

void Circle::print() const {
  printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id_, x_, y_,
         radius_, label_);
}

bool Circle::is_inside(int px, int py) const {
  return (px - x_) * (px - x_) + (py - y_) * (py - y_) <= radius_ * radius_;
}

void Circle::zoom(int factor) { radius_ *= factor; }
