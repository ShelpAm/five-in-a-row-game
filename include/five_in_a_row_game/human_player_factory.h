//
// Created by small-sheep on 11/20/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_HUMAN_PLAYER_FACTORY_H
#define FIVE_IN_A_ROW_GAME_SRC_HUMAN_PLAYER_FACTORY_H

#include "human_player.h"

class HumanPlayerFactory {
 public:
  HumanPlayerFactory();

  ~HumanPlayerFactory();

  HumanPlayer *MakePlayer() const;
};

#endif  // FIVE_IN_A_ROW_GAME_SRC_HUMAN_PLAYER_FACTORY_H
