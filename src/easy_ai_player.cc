//
// Created by small-sheep on 11/10/22.
//

#include "five_in_a_row_game/easy_ai_player.h"

#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/vector2d.h"

EasyAIPlayer::EasyAIPlayer() {}

EasyAIPlayer::EasyAIPlayer(const StoneType stone_type) : AIPlayer(stone_type) {}

EasyAIPlayer::~EasyAIPlayer() {}

const Vector2D<int> EasyAIPlayer::Think(const Board *board_ptr) const {
  //[TODO](small_sheep_): EASY_AI_PLAYER's THINKING PROCEDURE HAS NOT BEEN
  //  COMPLETED.
  // BoardCoordinate target_board_coordinate;
  BoardCoordinate target_board_coordinate;
  auto board = board_ptr->BoardMap();
  int end = board_ptr->BoardSize();
  for (int i = 0; i != end; ++i) {
    for (int j = 0; j != end; ++j) {
      target_board_coordinate.SetY(i);
      target_board_coordinate.SetX(j);

      if (board_ptr->StoneTypeInCoordinate(target_board_coordinate) ==
          StoneType::kStoneTypeEmpty) {
        return target_board_coordinate;
      }
    }
  }
  return target_board_coordinate;
}
