//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_PLAYER_FACTORY_H
#define FIVE_IN_A_ROW_GAME_SRC_PLAYER_FACTORY_H

#include <five_in_a_row_game/player.h>

class PlayerFactory {
 public:
  PlayerFactory();

  virtual ~PlayerFactory();

  virtual Player *MakePlayer() const = 0;
  virtual Player *MakePlayer(const StoneType stone_type) const = 0;
};

#endif  // FIVE_IN_A_ROW_GAME_SRC_PLAYER_FACTORY_H
