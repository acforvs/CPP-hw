#include "Scheme.hpp"
#include <cassert>

size_t Scheme::get_index_by_figure_id(int id) {
  for (size_t i = 0; i < sz_; i++) {
    if (figures_[i]->get_id() == id) {
      return i;
    }
  }
  assert(false && "No figure found by id");
}

Scheme::~Scheme() {
  for (size_t i = 0; i < sz_; i++) {
    delete figures_[i];
  }
  delete[] figures_;
}

Scheme::Scheme(int capacity) {
  figures_ = new Figure *[capacity];
  capacity_ = (size_t)capacity;
  sz_ = 0;
}

void Scheme::push_back_figure(Figure *fg) {
  assert((sz_ + 1 <= capacity_) && "Cannot add new figure: out of bounds");
  figures_[sz_] = fg;
  sz_++;
}

void Scheme::remove_figure(int id) {
  size_t ind = get_index_by_figure_id(id);
  delete figures_[ind];
  for (size_t i = ind; i < sz_ - 1; i++) {
    figures_[i] = figures_[i + 1];
  }
  sz_--;
}

void Scheme::print_all_figures() {
  for (size_t i = 0; i < sz_; i++) {
    figures_[i]->print();
  }
}

void Scheme::zoom_figure(int id, int factor) {
  size_t ind = get_index_by_figure_id(id);
  figures_[ind]->zoom(factor);
}

Figure *Scheme::is_inside_figure(int x, int y) {
  for (size_t i = 0; i < sz_; i++) {
    if (figures_[i]->is_inside(x, y)) {
      return figures_[i];
    }
  }
  return nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
  size_t ind = get_index_by_figure_id(id);
  figures_[ind]->move(new_x, new_y);
}
