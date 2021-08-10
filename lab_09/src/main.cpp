#include <stdio.h>

#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Scheme.hpp"

int main() {
  Scheme scheme(10);

  scheme.push_back_figure(new Rectangle(1, 5, 5, 10, 10));
  scheme.push_back_figure(new Circle(2, 3, 3, 3, "very nice circle"));

  scheme.print_all_figures();

  Figure *found = scheme.is_inside_figure(5, 5);
  if (found != nullptr) {
    found->print();
  } else {
    printf("not found\n");
  }

  scheme.zoom_figure(1, 2);
  scheme.print_all_figures();
  scheme.remove_figure(1);
  scheme.print_all_figures();

  return 0;
}
