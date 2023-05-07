#ifndef FIVE_IN_A_ROW_GAME_MOVE_H_
#define FIVE_IN_A_ROW_GAME_MOVE_H_

#include <ostream>
#include <sstream>

#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/stone_type.h"

class Move {
 public:
  Move(const BoardCoordinate & c, const StoneType st) {
    coordinate = c;
    stone_type = st;
  }
  BoardCoordinate coordinate;
  StoneType stone_type;
};

inline std::ostream & operator<<(std::ostream & os, const Move & move) {
  std::stringstream buf;
  buf << "Move {"
      << "\n  board_coordinate column & row:" << move.coordinate.column()
      << ", " << move.coordinate.row()
      << "\n  stone_type:" << stone_type_string_map().at(move.stone_type)
      << "\n}\n";
  os << buf.str();
  return os;
}

#endif  // FIVE_IN_A_ROW_GAME_MOVE_H_
