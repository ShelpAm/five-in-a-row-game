//
// Created by small-sheep on 11/10/22.
//

#include "five_in_a_row_game/ai_player.h"

#include "five_in_a_row_game/player.h"

AIPlayer::AIPlayer() {}

AIPlayer::AIPlayer(const Player & player) : Player(player) {}

AIPlayer::AIPlayer(const AIPlayer & other)
    : Player(other.Identity(), other.Name(), other.StoneTypeInUse()) {}

AIPlayer::AIPlayer(const AIPlayer && other) : Player(other) {}

AIPlayer::~AIPlayer() {}
