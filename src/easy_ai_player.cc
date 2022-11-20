//
// Created by small-sheep on 11/10/22.
//

#include "easy_ai_player.h"

EasyAIPlayer::EasyAIPlayer() {
}

EasyAIPlayer::EasyAIPlayer(const StoneType stone_type) : AIPlayer(stone_type) {
}

EasyAIPlayer::~EasyAIPlayer() {
}

const BoardCoordinate EasyAIPlayer::Think(const Board &board) const {
  //[TODO](small_sheep_): EASY_AI_PLAYER's THINKING PROCEDURE HAS NOT BEEN
  // COMPLETED.
  BoardCoordinate target_board_coordinate;
  for (int i = 0; i != board.BoardSize(); ++i) {
    for (int j = 0; j != board.BoardSize(); ++j) {
      target_board_coordinate.row = i;
      target_board_coordinate.column = j;
      if (board.StoneTypeInCoordinate(target_board_coordinate) ==
          StoneType::kStoneTypeEmpty) {
        return target_board_coordinate;
      }
    }
  }
  return target_board_coordinate;
}
