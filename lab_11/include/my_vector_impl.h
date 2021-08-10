#include <cassert>
#include <iostream>
#include <utility>

namespace containers {

template <typename T> int my_vector<T>::get_closest_2pw(int n) const {
  assert(n >= 0 && "cannot be less than zero");
  int res = 1;
  while (res < n) {
    res *= 2;
  }
  return res;
}

template <typename T> my_vector<T>::my_vector() {
  buf_ = new char[1 * sizeof(T)];
  array_ = reinterpret_cast<T *>(buf_);
  size_ = 0;
  capacity_ = 1;
}

template <typename T> my_vector<T>::my_vector(size_t n) {
  assert(n >= 0 && "Size should be >=0");
  size_t new_capacity = get_closest_2pw(n);
  buf_ = new char[new_capacity * sizeof(T)];
  array_ = reinterpret_cast<T *>(buf_);
  for (size_t i = 0; i < n; i++) {
    try {
      new (array_ + i) T();
    } catch (...) {
      free_partially(i);
      throw;
    }
  }
  size_ = n;
  capacity_ = new_capacity;
}

template <typename T> my_vector<T>::my_vector(const my_vector<T> &v) {
  buf_ = new char[v.capacity() * sizeof(T)];
  array_ = reinterpret_cast<T *>(buf_);
  for (size_t i = 0; i < v.size(); i++) {
    try {
      new (array_ + i) T(v[i]);
    } catch (...) {
      free_partially(i);
      throw;
    }
  }
  size_ = v.size();
  capacity_ = v.capacity();
}

template <typename T> my_vector<T>::~my_vector() {
  free();
  size_ = capacity_ = 0;
}

template <typename T> size_t my_vector<T>::size() const { return size_; }

template <typename T> size_t my_vector<T>::capacity() const {
  return capacity_;
}

template <typename T> void my_vector<T>::resize(size_t n) {
  assert(n >= 0 && "Size should be >=0");
  if (n == size_) {
    return;
  }

  if (n < size_) {
    while (size_ != n) {
      pop_back();
    }
    return;
  }

  if (n <= capacity_) {
    int cnt = 0;
    try {
      while (size_ != n) {
        new (array_ + size_) T();
        size_++;
        cnt++;
      }
    } catch (...) {
      while (cnt--) {
        pop_back();
      }
      throw;
    }
    size_ = n;
    return;
  }

  int new_cap = get_closest_2pw(n);
  char *new_buf = new char[new_cap * sizeof(T)];
  T *new_array(reinterpret_cast<T *>(new_buf));

  for (size_t i = 0; i < n; i++) {
    try {
      if (i < size_) {
        new (new_array + i) T(array_[i]);
      } else {
        new (new_array + i) T();
      }
    } catch (...) {
      for (size_t j = 0; j < i; j++) {
        new_array[j].~T();
      }
      delete[] new_buf;
      throw;
    }
  }
  free();
  buf_ = new_buf;
  capacity_ = new_cap;
  array_ = new_array;
  size_ = n;
}

template <typename T> void my_vector<T>::reserve(size_t n) {
  if (n <= capacity_) {
    return;
  }
  int new_cap = get_closest_2pw(n);
  char *new_buf = new char[new_cap * sizeof(T)];
  T *new_array(reinterpret_cast<T *>(new_buf));

  for (size_t i = 0; i < size_; i++) {
    try {
      new (new_array + i) T(array_[i]);
    } catch (...) {
      for (size_t j = 0; j < i; j++) {
        new_array[j].~T();
      }
      delete[] new_buf;
      throw;
    }
  }
  free();
  array_ = new_array;
  buf_ = new_buf;
  capacity_ = new_cap;
}

template <typename T> bool my_vector<T>::empty() const { return size_ == 0; }

template <typename T> void my_vector<T>::push_back(const T &t) {
  if (size_ < capacity_) {
    new (array_ + size_) T(t);
    size_++;
    return;
  }
  my_vector<T> copy(*this);
  copy.reserve(2 * copy.capacity_);
  new (copy.array_ + copy.size_++) T(t);
  my_vector<T>(copy).swap(*this);
}

template <typename T> void my_vector<T>::pop_back() {
  if (size_ == 0) {
    return;
  }
  array_[size_ - 1].~T();
  size_--;
}

template <typename T> void my_vector<T>::clear() {
  int sz = size_;
  while (sz--) {
    pop_back();
  }
}

template <typename T>
my_vector<T> &my_vector<T>::operator=(const my_vector<T> &v) {
  if (&v == this) {
    return *this;
  }
  my_vector<T>(v).swap(*this);
  return *this;
}

template <typename T> const T &my_vector<T>::operator[](size_t index) const {
  assert((0 <= index && index < size_) && "Incorrect index");
  return array_[index];
}

template <typename T> T &my_vector<T>::operator[](size_t index) {
  assert((0 <= index && index < size_) && "Incorrect index");
  return array_[index];
}

template <typename T> ostream &operator<<(ostream &out, const my_vector<T> &v) {
  if (v.size() == 0) {
    return out;
  }
  for (size_t i = 0; i < v.size() - 1; i++) {
    cout << v[i] << ' ';
  }
  cout << v[v.size() - 1];
  return out;
}

template <typename T> void my_vector<T>::swap(my_vector<T> &v) {
  std::swap(array_, v.array_);
  std::swap(buf_, v.buf_);
  std::swap(size_, v.size_);
  std::swap(capacity_, v.capacity_);
}

template <typename T> void my_vector<T>::free() { free_partially(size_); }

template <typename T> void my_vector<T>::free_partially(size_t i) {
  for (size_t j = 0; j < i; j++) {
    array_[j].~T();
  }
  delete[] buf_;
  buf_ = nullptr;
  array_ = nullptr;
}

} // namespace containers
