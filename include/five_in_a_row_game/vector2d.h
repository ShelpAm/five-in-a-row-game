#ifndef FIVE_IN_A_ROW_GAME_VECTOR2D_H_
#define FIVE_IN_A_ROW_GAME_VECTOR2D_H_

#include <cstddef>
#include <stdexcept>

template <typename T>
class Vector2D {
 public:
  using value_type = T;
  Vector2D();
  Vector2D(value_type x, value_type y);
  Vector2D(Vector2D<T> &&) = default;
  Vector2D(const Vector2D<T> &) = default;
  Vector2D<T> & operator=(Vector2D<T> &&) = default;
  Vector2D & operator=(const Vector2D &) = default;
  ~Vector2D() {}

  Vector2D<T> & operator+=(const Vector2D<T> & rhs);
  Vector2D<T> operator+(const Vector2D<T> & rhs) const;
  bool operator==(const Vector2D<T> & rhs) const;
  bool operator!=(const Vector2D<T> & rhs) const;

  value_type & operator[](std::size_t index) {
    return const_cast<value_type &>(
        static_cast<const Vector2D<T> &>(*this)[index]);
  }
  const value_type & operator[](std::size_t index) const {
    if (index > length() - 1) {
      throw std::runtime_error("index out of range");
    }
    return *(values_ + index);
  }

  value_type x() const { return values_[0]; }
  void set_x(value_type x) { values_[0] = x; }
  void add_x(value_type delta) { values_[0] += delta; }
  value_type y() const { return values_[1]; }
  void set_y(value_type y) { values_[1] = y; }
  void add_y(value_type delta) { values_[1] += delta; }

  static constexpr int length() { return 2; }

 private:
  value_type values_[2];
};

template <typename T>
Vector2D<T>::Vector2D() : values_{0, 0} {}

template <typename T>
Vector2D<T>::Vector2D(value_type x, value_type y) : values_{x, y} {}

template <typename T>
Vector2D<T> & Vector2D<T>::operator+=(const Vector2D<T> & rhs) {
  for (std::size_t i = 0; i != length() - 1; ++i) {
    (*this)[i] = rhs[i];
  }
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
  for (std::size_t i = 0; i != length(); ++i) {
    if ((*this)[i] != rhs[i]) {
      return true;
    }
  }
  return false;
}

#endif  // FIVE_IN_A_ROW_GAME_VECTOR2D_H_
