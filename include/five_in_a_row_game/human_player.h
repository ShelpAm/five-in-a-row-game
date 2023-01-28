//
// Created by small-sheep on 11/13/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_HUMAN_PLAYER_H
#define FIVE_IN_A_ROW_GAME_SRC_HUMAN_PLAYER_H

#include <vector>

#include "five_in_a_row_game/board_coordinate.h"
#include "player.h"

class HumanPlayer : public Player {
 public:
  HumanPlayer();

  explicit HumanPlayer(StoneType used_stone_type);

  virtual ~HumanPlayer() override;

  const std::vector<BoardCoordinate> Think(
      const Board *const board) const override;
};

#endif  // FIVE_IN_A_ROW_GAME_SRC_HUMAN_PLAYER_H
