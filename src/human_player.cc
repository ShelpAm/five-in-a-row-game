//
// Created by small-sheep on 11/13/22.
//

#include "five_in_a_row_game/human_player.h"

#include <iostream>
#include <vector>

#include "five_in_a_row_game/board_coordinate.h"

HumanPlayer::HumanPlayer(StoneType used_stone_type) : Player(used_stone_type) {}

HumanPlayer::HumanPlayer() {}

HumanPlayer::~HumanPlayer() {}

const std::vector<BoardCoordinate> HumanPlayer::Think(
    const Board *board_ptr) const {
  BoardCoordinate input_board_coordinate;
  auto TargetMoveIsValid = [board_ptr, &input_board_coordinate]() -> bool {
    return IsInRangeOf(input_board_coordinate, board_ptr) &&
           board_ptr->StoneTypeInCoordinate(input_board_coordinate) ==
               StoneType::kStoneTypeEmpty;
  };

  std::cout << "Please input your move(first column and then row; every "
               "input should be followed by an ENTER):\n";
  while (true) {
    std::cin >> input_board_coordinate[0] >> input_board_coordinate[1];
    if (TargetMoveIsValid()) {
      break;
    }
    // The move is invalid.
    std::cout << "Your target coordinate is invalid, please choose another "
                 "one!\n";
  }
  return std::vector<BoardCoordinate>{input_board_coordinate};
}
