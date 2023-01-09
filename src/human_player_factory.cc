//
// Created by small-sheep on 11/20/22.
//

#include "five_in_a_row_game/human_player.h"
#include "five_in_a_row_game/human_player_factory.h"

HumanPlayerFactory::HumanPlayerFactory() {}

HumanPlayerFactory::~HumanPlayerFactory() {}

Player *HumanPlayerFactory::MakePlayer() const { return new HumanPlayer; }

Player *HumanPlayerFactory::MakePlayer(const StoneType stone_type) const {
  return new HumanPlayer(stone_type);
}
