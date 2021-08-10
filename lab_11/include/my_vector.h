#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>

namespace containers {

using namespace std;

template <typename T> class my_vector {
public:
  my_vector();
  my_vector(std::size_t n);
  my_vector(const my_vector<T> &other);
  my_vector &operator=(const my_vector<T> &other);
  ~my_vector();

  std::size_t size() const;
  std::size_t capacity() const;
  bool empty() const;

  void resize(std::size_t n);
  void reserve(std::size_t n);

  const T &operator[](std::size_t index) const;
  T &operator[](std::size_t index);

  void push_back(const T &t);
  void pop_back();
  void clear();

private:
  int get_closest_2pw(int n) const;
  void swap(my_vector<T> &v);
  void free();
  void free_partially(size_t i);

private:
  size_t capacity_;
  size_t size_;
  T *array_;
  char *buf_;
};

} // namespace containers

#include "my_vector_impl.h"

#endif // MY_VECTOR_H_
