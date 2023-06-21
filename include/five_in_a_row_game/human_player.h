//
// Created by small-sheep on 11/13/22.
//

#ifndef FIVE_IN_A_ROW_GAME_HUMAN_PLAYER_H
#define FIVE_IN_A_ROW_GAME_HUMAN_PLAYER_H

#include <vector>

#include "five_in_a_row_game/board_coordinate.h"
#include "player.h"

class HumanPlayer : public Player {
 public:
  HumanPlayer();

  explicit HumanPlayer(const Player * const player);

  virtual ~HumanPlayer() override;

 private:
  const BoardCoordinateContainer Think(const GameBoard & board) const override;
};

#endif  // FIVE_IN_A_ROW_GAME_HUMAN_PLAYER_H
