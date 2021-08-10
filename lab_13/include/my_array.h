#include <cassert>
#include <cstdint>

namespace lab_13 {

template <typename T, std::size_t N> class my_array {
public:
  my_array() = default;

  const T &at(std::size_t index) const {
    assert((0 <= index && index < N) && "Index out of range");
    return arr_[index];
  };

  T &at(std::size_t index) {
    assert((0 <= index && index < N) && "Index out of range");
    return arr_[index];
  }

  const T &operator[](std::size_t index) const { return arr_[index]; };

  T &operator[](std::size_t index) { return arr_[index]; };

  bool empty() const { return N == 0; };

  std::size_t size() const { return N; };

  void fill(T val) {
    for (std::size_t i = 0; i < N; i++) {
      arr_[i] = val;
    }
  };

private:
  T arr_[N];
};

template <std::size_t N> class my_array<bool, N> {

  struct BitReference {
    BitReference(uint8_t *byte, std::size_t bit) : byte_(byte), bit_n_(bit){};

    BitReference &operator=(bool b) {
      if (b) {
        *byte_ |= (1 << bit_n_);
      } else {
        *byte_ &= ~(1 << bit_n_);
      }
      return *this;
    }

    BitReference &operator=(BitReference &br) {
      byte_ = br.byte_;
      bit_n_ = br.bit_n_;
      return *this;
    }

    operator bool() const { return *byte_ & (1 << bit_n_); }

    uint8_t *byte_;
    std::size_t bit_n_;
  };

public:
  my_array() {
    for (std::size_t i = 0; i < N; i++) {
      arr_[i / 8] = 0;
    }
  };

  std::size_t size() const { return N; };
  bool empty() const { return N == 0; };

  void fill(bool val) {
    for (std::size_t i = 0; i < N; i++) {
      if (val) {
        arr_[i / 8] |= (1 << (i % 8));
      } else {
        arr_[i / 8] = 0;
      }
    }
  };

  bool at(std::size_t index) const {
    assert((0 <= index && index < N) && "Index out of range");
    return arr_[index / 8] & (1 << (index % 8));
  }

  BitReference at(std::size_t index) {
    assert((0 <= index && index < N) && "Index out of range");
    return BitReference(&arr_[index / 8], index % 8);
  }

  bool operator[](std::size_t index) const {
    return arr_[index / 8] & (1 << (index % 8));
  }

  BitReference operator[](std::size_t index) {
    return BitReference(&arr_[index / 8], index % 8);
  }

private:
  uint8_t arr_[(N + 7) / 8];
};

} // namespace lab_13
