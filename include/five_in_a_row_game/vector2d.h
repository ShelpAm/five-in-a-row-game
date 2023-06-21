#ifndef FIVE_IN_A_ROW_GAME_VECTOR2D_H
#define FIVE_IN_A_ROW_GAME_VECTOR2D_H

#include <cassert>
#include <cstddef>
#include <stdexcept>

template <typename T>
class Vector2D {
 public:
  using value_type = T;
  Vector2D() = default;
  Vector2D(value_type x, value_type y);
  Vector2D(Vector2D<T> &&) = default;
  Vector2D(const Vector2D<T> &) = default;
  Vector2D<T> & operator=(Vector2D<T> &&) = default;
  Vector2D & operator=(const Vector2D &) = default;
  ~Vector2D() = default;

  Vector2D<T> & operator+=(const Vector2D<T> & rhs);

  Vector2D<T> operator+(const Vector2D<T> & rhs) const;

  Vector2D<T> operator*(const T scale) const {
    return Vector2D<T>(x() * scale, y() * scale);
  }

  bool operator==(const Vector2D<T> & rhs) const;
  bool operator!=(const Vector2D<T> & rhs) const;
  // bool operator<(const Vector2D<T> & rhs) const {
  // return values_[0] < rhs.values_[0] || values_[1] < rhs.values_[1];
  //}

  value_type & operator[](std::size_t index) {
    return const_cast<value_type &>(
        static_cast<const Vector2D<T> &>(*this)[index]);
  }
  const value_type & operator[](std::size_t index) const {
    if (index >= length()) {
      assert(false);
      throw std::runtime_error("index out of range");
    }
    return *(&x_ + index);
  }

  value_type x() const { return x_; }
  void set_x(const value_type x) { x_ = x; }
  void add_x(const value_type delta) { x_ += delta; }
  value_type y() const { return y_; }
  void set_y(const value_type y) { y_ = y; }
  void add_y(const value_type delta) { y_ += delta; }

  static constexpr int length() { return 2; }

 private:
  value_type x_;
  value_type y_;
};

template <typename T>
Vector2D<T>::Vector2D(value_type x, value_type y) : x_(x), y_(y) {}

template <typename T>
Vector2D<T> & Vector2D<T>::operator+=(const Vector2D<T> & rhs) {
  add_x(rhs.x());
  add_y(rhs.y());
  return *this;
}

template <typename T>
Vector2D<T> Vector2D<T>::operator+(const Vector2D<T> & rhs) const {
  return Vector2D<T>{*this} += rhs;
}

template <typename T>
bool Vector2D<T>::operator==(const Vector2D<T> & rhs) const {
  return !(*this != rhs);
}

template <typename T>
bool Vector2D<T>::operator!=(const Vector2D<T> & rhs) const {
  if (x() != rhs.x() || y() != rhs.y()) {
    return true;
  }
  return false;
}

#endif  // FIVE_IN_A_ROW_GAME_VECTOR2D_H
