//
// Created by small-sheep on 11/13/22.
//

#include "five_in_a_row_game/human_player.h"

#include <iostream>

HumanPlayer::HumanPlayer(StoneType used_stone_type) : Player(used_stone_type) {
}

HumanPlayer::HumanPlayer() {
}

HumanPlayer::~HumanPlayer() {
}

const BoardCoordinate HumanPlayer::Think(const Board *board_ptr) const {
  bool target_move_is_valid = false;
  BoardCoordinate input_board_coordinate;
  do {
    std::cout << "Please input your move(first row and then column; every "
                 "input should be followed by an ENTER):\n";
    std::cin >> input_board_coordinate.row >> input_board_coordinate.column;
    target_move_is_valid =
        board_ptr->StoneTypeInCoordinate(input_board_coordinate) ==
        StoneType::kStoneTypeEmpty;
    if (!target_move_is_valid) {
      std::cout << "Your target coordinate is invalid, please choose another "
                   "one!\n";
    }
  } while (!target_move_is_valid);
  return input_board_coordinate;
}
