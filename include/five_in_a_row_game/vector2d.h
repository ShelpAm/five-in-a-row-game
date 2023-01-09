#ifndef FIVE_IN_A_ROW_GAME_VECTOR2D_H_
#define FIVE_IN_A_ROW_GAME_VECTOR2D_H_

#include <exception>

template <typename T>
class Vector2D {
 public:
  using value_type = T;
  Vector2D();
  Vector2D(value_type x, value_type y);

  value_type &operator[](int index) {
    if (index > length() - 1 || index < 0) {
      throw std::exception();
    }
    return *(values_ + index);
  }
  const value_type &operator[](int index) const {
    if (index > length() - 1 || index < 0) {
      throw std::exception();
    }
    return *(values_ + index);
  }

  value_type X() const { return values_[0]; }
  void SetX(value_type x) { values_[0] = x; }
  void AddX(value_type x) { values_[0] += x; }

  value_type Y() const { return values_[1]; }
  void SetY(value_type y) { values_[1] = y; }
  void AddY(value_type y) { values_[1] += y; }

 private:
  static constexpr int length() { return 2; }
  value_type values_[2];
};

template <typename T>
Vector2D<T>::Vector2D() : values_{0, 0} {}

template <typename T>
Vector2D<T>::Vector2D(value_type x, value_type y) : values_{x, y} {}

#endif  // FIVE_IN_A_ROW_GAME_VECTOR2D_H_
