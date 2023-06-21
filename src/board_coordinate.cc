//
// Created by small-sheep on 11/11/22.
//

#include "five_in_a_row_game/board_coordinate.h"

#include "five_in_a_row_game/vector2d.h"

BoardCoordinate::BoardCoordinate() : vector2i_() {}

BoardCoordinate::BoardCoordinate(const Vector2D<int> & vec2i)
    : vector2i_(vec2i) {}

BoardCoordinate::BoardCoordinate(int x, int y) : vector2i_(x, y) {}

bool BoardCoordinate::operator<(const BoardCoordinate & rhs) const {
  if (vector2i_.x() < rhs.x()) {
    return true;
  } else if (vector2i_.x() == rhs.x()) {
    if (vector2i_.y() < rhs.y()) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}
bool BoardCoordinate::operator==(const BoardCoordinate & rhs) const {
  return vector2i_ == rhs.vector2i_;
}
bool BoardCoordinate::operator!=(const BoardCoordinate & rhs) const {
  return vector2i_ != rhs.vector2i_;
}
BoardCoordinate::operator Vector2D<int>() const { return vector2i_; }
