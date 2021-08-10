#include <iostream>

#include "my_vector.h"

namespace product {

using namespace std;

class Product {
public:
  Product(const string name, int quantity, double price)
      : name_(name), quantity_(quantity), price_(price){};

  Product(const Product &p) {
    name_ = p.name_;
    quantity_ = p.quantity_;
    price_ = p.price_;
  };

  ~Product(){};

  friend ostream &operator<<(ostream &out, const Product &p) {
    cout << p.name_ << ' ' << p.quantity_ << ' ' << p.price_;
    return out;
  }

  bool operator==(const Product &p) const {
    return (p.name_ == name_ && p.quantity_ == quantity_ && p.price_ == price_);
  }

private:
  string name_;
  int quantity_;
  double price_;
};

void print(const containers::my_vector<Product> &v) { cout << v << endl; }

} // namespace product

template <typename T> void test_my_vector(T a, T b) {
  containers::my_vector<T> array;
  assert(array.size() == 0 && "Incorrect init size");
  assert(array.capacity() == 1 && "Incorrect init capacity");

  try {
    array.push_back(a);
  } catch (...) {
    std::cout << "test_my_vector: push_back error" << std::endl;
    throw;
  }
  assert(array.size() == 1 && "Incorrect size after push_back");

  try {
    array.push_back(b);
  } catch (...) {
    std::cout << "test_my_vector: push_back error" << std::endl;
    throw;
  }
  assert(array.size() == 2 && "Incorrect size after push_back");
  assert(array.capacity() == 2 && "Incorrect capacity after 2 push_backs");
  assert((array[0] == a && array[1] == b) && "Incorrect elements");

  array[0] = b;
  assert((array[0] == b) && "operator[] doesn't work for lvalue");

  try {
    array.push_back(a);
  } catch (...) {
    std::cout << "test_my_vector: push_back error" << std::endl;
    throw;
  }
  assert(array.capacity() == 4 &&
         "Incorrect capacity change after 3rd push_back");
  try {
    array.reserve(20);
  } catch (...) {
    std::cout << "test_my_vector: reserve error" << std::endl;
    throw;
  }
  assert(array.capacity() == 32 && "Incorrect capacity after reserver(20)");

  try {
    array.reserve(100);
  } catch (...) {
    std::cout << "test_my_vector: reserve error" << std::endl;
    throw;
  }
  assert(array.capacity() == 128 && "Incorrect capacity after reserve(100)");

  try {
    array.reserve(128);
  } catch (...) {
    std::cout << "test_my_vector: reserve error" << std::endl;
    throw;
  }
  assert(array.capacity() == 128 && "Incorrect capacity after reserve(128)");
  // === === === TEST COPY AND OPERATORS === === ===

  containers::my_vector<T> equal_array;

  equal_array = array;
  assert((array.size() == equal_array.size() &&
          array.capacity() == equal_array.capacity()) &&
         "Operator= incorrectly copies size or capacity");

  for (size_t i = 0; i < array.size(); i++) {
    assert(array[i] == equal_array[i] &&
           "Operator= incorrectly copies elements");
  }

  containers::my_vector<T> copied_array(array);
  assert((copied_array.size() == array.size() &&
          copied_array.capacity() == array.capacity()) &&
         "Copy constructor incorrectyle copies size or capacity");

  for (size_t i = 0; i < array.size(); i++) {
    assert(array[i] == copied_array[i] &&
           "Copy constructor incorrectly copies elements");
  }
  copied_array.clear();
  assert(copied_array.size() == 0 && "clear() doesn't set the size to 0");
  assert(!array.empty() && copied_array.empty() && "empty() is incorrect");

  array = array = copied_array;
  std::cout << "Tests have passed for general case" << std::endl;
}

template <typename T> void test_my_vector_default_constructible(T a, T b) {
  containers::my_vector<T> array(5);
  assert(array.size() == 5 && array.capacity() == 8 &&
         "my_vector(int n) incorrectly sets size or capacity");
  try {
    array.push_back(a);
    array.push_back(b);
    array.push_back(a);
  } catch (...) {
    std::cout << "test_my_vector_default_constructible: push_back error"
              << std::endl;
    throw;
  }
  assert(array.size() == 8 && "Incorrect push_back");

  try {
    array.resize(6);
  } catch (...) {
    std::cout << "test_my_vector_default_constructible: resize error, new_size "
                 "< size_"
              << std::endl;
    throw;
  }
  assert(array.size() == 6 && "Size is incorrect after resize");

  try {
    array.resize(8);
  } catch (...) {
    std::cout << "test_my_vector_default_constructible: resize error, size_ < "
                 "new_size = capacity_"
              << std::endl;
    throw;
  }
  assert(array[7] != a && "Elements are not set to default after resize");

  try {
    array.push_back(a);
  } catch (...) {
    std::cout << "test_my_vector_default_constructible: push_back error"
              << std::endl;
    throw;
  }
  assert(array.capacity() == 16 && "Incorrect capacity after push_back");

  try {
    array.resize(10);
  } catch (...) {
    std::cout << "test_my_vector_default_constructible: resize error, size_ < "
                 "new_size < capacity_"
              << std::endl;
    throw;
  }
  assert((array.size() == 10 && array.capacity() == 16) &&
         "Incorrect capacity or size after push_back");

  try {
    array.resize(1000);
  } catch (...) {
    std::cout << "test_my_vector_default_constructible: resize error: "
                 "capacity_ < new_size"
              << std::endl;
    throw;
  }
  assert((array.size() == 1000 && array.capacity() == 1024) &&
         "Incorrect capacity or size after push_back");

  std::cout << "Tests have passed for default_constructible" << std::endl;
}

int main() {
  using namespace product;

  test_my_vector<int>(5, 10);
  test_my_vector<Product>(Product("very nice", 239, 11.1),
                          Product("kek mem spasite", -1, 7.5));
  test_my_vector_default_constructible<int>(3, 100);

  return 0;
}
