//
// Created by small-sheep on 11/20/22.
//

#include "human_player_factory.h"

#include "human_player.h"

HumanPlayerFactory::HumanPlayerFactory() {

}

HumanPlayerFactory::~HumanPlayerFactory() {

}

Player *HumanPlayerFactory::MakePlayer() const {
  return new HumanPlayer;
}
Player *HumanPlayerFactory::MakePlayer(const StoneType stone_type) const {
  return new HumanPlayer(stone_type);
}
