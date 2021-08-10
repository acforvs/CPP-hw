#include "my_array.h"
#include <cstddef>

using lab_13::my_array;

template <typename T, std::size_t N> void test_core() {
  my_array<T, N> a;
  const my_array<T, N> &ca = a;
  a.empty();
  ca.empty();
  a.size();
  ca.size();

  a.at(0);
  ca.at(0);
  a[0];
  ca[0];

  (void)static_cast<const T &>(a[0]);
  (void)static_cast<const T &>(ca[0]);
}

void test_bool() {
  my_array<bool, 10> a;
  a[0] = 1;
  a[1] = 1;
  a[2] = 0;
  a[3] = 0;
  a[8] = 1;

  a.at(6) = 1;
  a[6] = a.at(6);
  a[5] = a[6];

  (a[5] = a[6]) = 1;
  (a[5] = a[6]) = 0;
  a[5] = a[6] = a[6] = 1;

  a.fill(1);
  a.fill(0);
}

template <typename T, std::size_t N> void test_assign() {
  my_array<T, N> a;
  const my_array<T, N> &ca = a;
  a.fill(T());

  a[0] = T();
  a[0] = a[0];
  a[0] = ca[0];
}

class NonCopyable {
public:
  NonCopyable() {}

private:
  NonCopyable(const NonCopyable &);
  NonCopyable &operator=(const NonCopyable);
};

int main() {
  test_core<int, 10>();
  test_core<bool, 10>();
  test_core<NonCopyable, 10>();

  test_bool();

  test_assign<int, 10>();
  test_assign<bool, 10>();
}
