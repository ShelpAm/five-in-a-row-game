#ifndef FIVE_IN_A_ROW_GAME_VECTOR2D_H_
#define FIVE_IN_A_ROW_GAME_VECTOR2D_H_

template <typename value_type>
class Vector2D {
 public:
  Vector2D();
  Vector2D(value_type x, value_type y);

  value_type &operator[](int index);

  value_type X() const { return values[0]; }
  value_type Y() const { return values[1]; }

  void SetX(value_type x) { values[0] = x; }
  void SetY(value_type y) { values[1] = y; }

 private:
  value_type values[2];
};

template <typename value_type>
Vector2D<value_type>::Vector2D() : values{0, 0} {}

template <typename value_type>
Vector2D<value_type>::Vector2D(value_type x, value_type y) : values{x, y} {}

template<typename value_type>
value_type &Vector2D<value_type>::operator[](int index) {
  return *(values + index);
}

#endif  // FIVE_IN_A_ROW_GAME_VECTOR2D_H_
