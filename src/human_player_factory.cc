//
// Created by small-sheep on 11/20/22.
//

#include "five_in_a_row_game/human_player_factory.h"

#include "five_in_a_row_game/human_player.h"

HumanPlayerFactory::HumanPlayerFactory() {}

HumanPlayerFactory::~HumanPlayerFactory() {}

HumanPlayer *HumanPlayerFactory::MakePlayer() const { return new HumanPlayer; }
