//
// Created by small-sheep on 11/10/22.
//

#include "five_in_a_row_game/easy_ai_player_factory.h"

#include <memory>

#include "five_in_a_row_game/easy_ai_player.h"
#include "five_in_a_row_game/easy_ai_player_fwd.h"

EasyAIPlayerFactory::EasyAIPlayerFactory() {}

EasyAIPlayerFactory::~EasyAIPlayerFactory() {}

std::shared_ptr<EasyAIPlayer> EasyAIPlayerFactory::MakePlayer(
    const int id, const char * name) const {
  auto ptr = std::make_shared<EasyAIPlayer>();
  ptr->set_name(name);
  ptr->set_id(id);
  return ptr;
}
