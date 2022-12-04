//
// Created by small-sheep on 11/10/22.
//

#include "five_in_a_row_game/easy_ai_player.h"

EasyAIPlayer::EasyAIPlayer() {
}

EasyAIPlayer::EasyAIPlayer(const StoneType stone_type) : AIPlayer(stone_type) {
}

EasyAIPlayer::~EasyAIPlayer() {
}

const BoardCoordinate EasyAIPlayer::Think(const Board *board_ptr) const {
  //[TODO](small_sheep_): EASY_AI_PLAYER's THINKING PROCEDURE HAS NOT BEEN
  //  COMPLETED.
  BoardCoordinate target_board_coordinate;
  for (int i = 0; i != board_ptr->BoardSize(); ++i) {
    for (int j = 0; j != board_ptr->BoardSize(); ++j) {
      target_board_coordinate.row = i;
      target_board_coordinate.column = j;
      if (board_ptr->StoneTypeInCoordinate(target_board_coordinate) ==
          StoneType::kStoneTypeEmpty) {
        return target_board_coordinate;
      }
    }
  }
  return target_board_coordinate;
}
