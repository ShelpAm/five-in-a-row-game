//
// Created by small-sheep on 11/10/22.
//

#include <five_in_a_row_game/easy_ai_player_factory.h>
#include <five_in_a_row_game/easy_ai_player.h>

EasyAIPlayerFactory::EasyAIPlayerFactory() {
}

EasyAIPlayerFactory::~EasyAIPlayerFactory() {
}

Player *EasyAIPlayerFactory::MakePlayer() const {
  return new EasyAIPlayer;
}

Player *EasyAIPlayerFactory::MakePlayer(const StoneType stone_type) const {
  return new EasyAIPlayer(stone_type);
}

