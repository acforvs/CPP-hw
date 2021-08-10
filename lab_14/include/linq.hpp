#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>

namespace linq {
namespace impl {

template <typename T, typename Iter> class range_enumerator;
template <typename T> class drop_enumerator;
template <typename T> class take_enumerator;
template <typename T, typename U, typename F> class select_enumerator;
template <typename T, typename F> class until_enumerator;
template <typename T, typename F> class where_enumerator;

template <typename T> class enumerator {
public:
  enumerator(const enumerator &) = delete;
  enumerator &operator=(const enumerator &) = delete;
  enumerator &operator=(enumerator &&) = delete;
  enumerator(enumerator &&) = default;
  enumerator() = default;

  virtual const T &operator*() = 0;
  virtual enumerator &operator++() = 0;
  virtual operator bool() const = 0;

  auto drop(int count) && { return drop_enumerator<T>(*this, count); }

  template <typename U = T, typename F> auto select(F &&func) && {
    return select_enumerator<U, T, F>(*this, std::move(func));
  }

  template <typename F> auto until(F &&func) && {
    return until_enumerator<T, F>(*this, std::move(func));
  }

  auto until_eq(const T &v) && {
    auto f = [v](const T &a) { return v == a; };
    return std::move(*this).until(std::move(f));
  }

  template <typename Iter> void copy_to(Iter it) && {
    enumerator &self = *this;
    while (self) {
      *it = *self;
      ++it;
      ++self;
    }
  }

  std::vector<T> to_vector() && {
    std::vector<T> v;
    std::move(*this).copy_to(std::back_inserter(v));
    return v;
  }

  auto take(int count) && { return take_enumerator<T>(*this, count); }

  template <typename F> auto where(F &&predicate) && {
    return where_enumerator<T, F>(*this, std::move(predicate));
  }

  auto where_neq(const T &v) && {
    auto f = [v](const T &a) { return v != a; };
    return std::move(*this).where(std::move(f));
  }
};

template <typename T, typename Iter>
class range_enumerator : public enumerator<T> {
public:
  range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}
  operator bool() const override { return begin_ != end_; }
  const T &operator*() override { return *begin_; }
  range_enumerator &operator++() override {
    ++begin_;
    return *this;
  }

private:
  Iter begin_, end_;
};

template <typename T> class take_enumerator : public enumerator<T> {
public:
  take_enumerator(enumerator<T> &parent, int count)
      : parent_(parent), count_(count) {}
  operator bool() const override { return count_ && parent_; }
  const T &operator*() override { return *parent_; }
  take_enumerator &operator++() override {
    count_--;
    if (count_) {
      ++parent_;
    }
    return *this;
  }

private:
  enumerator<T> &parent_;
  int count_;
};

template <typename T> class drop_enumerator : public enumerator<T> {
public:
  drop_enumerator(enumerator<T> &parent, int count) : parent_(parent) {
    while (parent_ && count > 0) {
      ++parent_;
      --count;
    }
  }
  operator bool() const override { return parent_; }
  const T &operator*() override { return *parent_; }
  drop_enumerator &operator++() override {
    ++parent_;
    return *this;
  }

private:
  enumerator<T> &parent_;
};

template <typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
public:
  select_enumerator(enumerator<U> &parent, F &&func)
      : parent_(parent), func_(std::move(func)) {
    if (parent_)
      cache_ = func_(*parent_);
  }
  operator bool() const override { return parent_; }
  const T &operator*() override { return cache_; }
  select_enumerator &operator++() override {
    ++parent_;
    if (parent_)
      cache_ = func_(*parent_);
    return *this;
  }

private:
  enumerator<U> &parent_;
  T cache_;
  F func_;
};

template <typename T, typename F>
class until_enumerator : public enumerator<T> {
public:
  until_enumerator(enumerator<T> &parent, F &&predicate)
      : parent_(parent), predicate_(std::move(predicate)) {
    if (parent_)
      cache_ = predicate_(*parent_);
  }
  operator bool() const override { return parent_ && !cache_; }
  const T &operator*() override { return *parent_; }
  until_enumerator &operator++() override {
    ++parent_;
    if (parent_)
      cache_ = predicate_(*parent_);
    return *this;
  }

private:
  enumerator<T> &parent_;
  F predicate_;
  T cache_;
};

template <typename T, typename F>
class where_enumerator : public enumerator<T> {
public:
  where_enumerator(enumerator<T> &parent, F &&predicate)
      : parent_(parent), predicate_(std::move(predicate)) {
    for (; parent_ && !predicate_(*parent_); ++parent_)
      ;
  }
  operator bool() const override { return parent_; }
  const T &operator*() override { return *parent_; }
  where_enumerator &operator++() override {
    for (; ++parent_ && !predicate_(*parent_);)
      ;
    return *this;
  }

private:
  enumerator<T> &parent_;
  F predicate_;
};

} // namespace impl

template <class Iter> auto from(Iter begin, Iter end) {
  using value_type = typename std::iterator_traits<Iter>::value_type;
  return impl::range_enumerator<value_type, Iter>(begin, end);
}

} // namespace linq

#endif
