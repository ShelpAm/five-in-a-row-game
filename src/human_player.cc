//
// Created by small-sheep on 11/13/22.
//

#include "five_in_a_row_game/human_player.h"

#include <iostream>
#include <vector>

#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/player.h"

HumanPlayer::HumanPlayer() {}

HumanPlayer::HumanPlayer(const Player * const player) : Player(*player) {}

HumanPlayer::~HumanPlayer() {}

const std::vector<BoardCoordinate> HumanPlayer::Think(
    const Board & board) const {
  BoardCoordinate input_coordinate;
  auto TargetMoveIsValid = [board, &input_coordinate]() -> bool {
    return CoordinateIsInRangeOfBoard(input_coordinate, board) &&
           board.StoneTypeInCoordinate(input_coordinate) ==
               StoneType::kStoneTypeEmpty;
  };

  std::cout << "Please input your move(first column and then row; every "
               "input should be followed by an ENTER):\n";
  while (true) {
    std::cin >> input_coordinate[0] >> input_coordinate[1];
    if (TargetMoveIsValid()) {
      break;
    }
    // The move is invalid.
    std::cout << "Your target coordinate is invalid, please choose another "
                 "one!\n";
  }
  return std::vector<BoardCoordinate>{input_coordinate};
}
