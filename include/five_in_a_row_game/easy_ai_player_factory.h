//
// Created by small-sheep on 11/10/22.
//

#ifndef FIVE_IN_A_ROW_GAME_EASY_AI_PLAYER_FACTORY_H
#define FIVE_IN_A_ROW_GAME_EASY_AI_PLAYER_FACTORY_H

#include <memory>

#include "five_in_a_row_game/easy_ai_player_fwd.h"

class EasyAIPlayerFactory {
 public:
  static EasyAIPlayerFactory & Instance() {
    static EasyAIPlayerFactory instance;
    return instance;
  }

  std::shared_ptr<EasyAIPlayer> MakePlayer() const;

 private:
  EasyAIPlayerFactory();
  ~EasyAIPlayerFactory();
};

#endif  // FIVE_IN_A_ROW_GAME_EASY_AI_PLAYER_FACTORY_H
