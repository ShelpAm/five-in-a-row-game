//
// Created by small-sheep on 11/20/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_HUMAN_PLAYER_FACTORY_H
#define FIVE_IN_A_ROW_GAME_SRC_HUMAN_PLAYER_FACTORY_H

#include <memory>

#include "human_player.h"

class HumanPlayerFactory {
 public:
  static HumanPlayerFactory & Instance() {
    static HumanPlayerFactory instance;
    return instance;
  }

  std::shared_ptr<HumanPlayer> MakePlayer() const;

 private:
  HumanPlayerFactory();
  ~HumanPlayerFactory();
};

#endif  // FIVE_IN_A_ROW_GAME_SRC_HUMAN_PLAYER_FACTORY_H
