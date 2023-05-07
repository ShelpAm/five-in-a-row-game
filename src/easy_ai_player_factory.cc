//
// Created by small-sheep on 11/10/22.
//

#include "five_in_a_row_game/easy_ai_player_factory.h"

#include <memory>

#include "five_in_a_row_game/easy_ai_player.h"
#include "five_in_a_row_game/easy_ai_player_fwd.h"

EasyAIPlayerFactory::EasyAIPlayerFactory() {}

EasyAIPlayerFactory::~EasyAIPlayerFactory() {}

std::shared_ptr<EasyAIPlayer> EasyAIPlayerFactory::MakePlayer() const {
  return std::make_shared<EasyAIPlayer>();
}
