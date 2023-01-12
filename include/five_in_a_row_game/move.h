#ifndef FIVE_IN_A_ROW_GAME_MOVE_H_
#define FIVE_IN_A_ROW_GAME_MOVE_H_

#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/stone_type.h"

class Move {
 public:
  BoardCoordinate board_coordinate;
  StoneType stone_type;
};

#endif  // FIVE_IN_A_ROW_GAME_MOVE_H_
