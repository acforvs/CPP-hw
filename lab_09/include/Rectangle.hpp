#include "Figure.hpp"

class Rectangle : public Figure {
public:
  Rectangle(int id, int x, int y, int width, int height);
  ~Rectangle();

  void print() const override;
  void zoom(int factor) override;
  bool is_inside(int x, int y) const override;

private:
  int width_;
  int height_;
};
