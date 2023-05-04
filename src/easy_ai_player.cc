//
// Created by small-sheep on 11/10/22.
//

#include "five_in_a_row_game/easy_ai_player.h"

#include <math.h>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iterator>
#include <vector>

#include "five_in_a_row_game/ai_player.h"
#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/stone_type.h"

EasyAIPlayer::EasyAIPlayer() {}

EasyAIPlayer::EasyAIPlayer(const AIPlayer * const ai_player)
    : AIPlayer(*ai_player) {}

EasyAIPlayer::~EasyAIPlayer() {}

const std::vector<BoardCoordinate> EasyAIPlayer::Think(
    const Board & board) const {
  auto score_map{CalculateScore(board)};
  std::size_t current_maximum_score{0};
  std::vector<BoardCoordinate> coords_of_maximum_score;

  int end = static_cast<int>(board.board_size());
  for (int column = 0; column != end; ++column) {
    for (int row = 0; row != end; ++row) {
      if (current_maximum_score < score_map[column][row]) {
        current_maximum_score = score_map[column][row];
        coords_of_maximum_score.clear();
        coords_of_maximum_score.push_back(BoardCoordinate(column, row));
      } else if (current_maximum_score == score_map[column][row]) {
        coords_of_maximum_score.push_back(BoardCoordinate(column, row));
      }
    }
  }
  return coords_of_maximum_score;
}

const std::vector<std::vector<std::size_t>> EasyAIPlayer::CalculateScore(
    const Board & board) const {
  std::vector<std::vector<std::size_t>> score_map{
      board.board_size(), std::vector<size_t>(board.board_size(), 0)};
  int end = static_cast<int>(board.board_size());
  for (int column = 0; column != end; ++column) {
    for (int row = 0; row != end; ++row) {
      if (board.GetStoneTypeInCoordinate(BoardCoordinate{column, row}) !=
          StoneType::kStoneTypeEmpty) {
        continue;
      }
      // TODO(small-sheep): what is the intention of the following line?
      std::size_t my_stone_sum = 0, enemy_stone_sum = 0, empty_stone_sum = 0;
      // 8 directions
      for (int horizontal = -1; horizontal != 2; ++horizontal) {
        for (int vertical = -1; vertical != 2; ++vertical) {
          if (horizontal == 0 && vertical == 0) {
            continue;
          }
          // Here starts calculating.
          std::size_t direction_enemy_stone_num{0}, direction_my_stone_num{0};
          std::size_t direction_length_sum{1};
          for (int length = 1; length != 5; ++length) {
            int current_column{column + horizontal * length},
                current_row{row + vertical * length};
            const BoardCoordinate current_coordinate{current_column,
                                                     current_row};
            if (!IsCoordinateInRangeOfBoard(current_coordinate, board)) {
              break;
            }
            StoneType current_stone_type =
                board.GetStoneTypeInCoordinate(current_coordinate);
            if (current_stone_type == stone_type_in_use()) {
              ++direction_my_stone_num;
              ++my_stone_sum;
              direction_length_sum += length;
            } else if (current_stone_type == StoneType::kStoneTypeEmpty) {
              ++empty_stone_sum;
            } else {
              ++direction_enemy_stone_num;
              ++enemy_stone_sum;
              direction_length_sum += length;
            }
          }
          score_map[column][row] +=
              20 *
              (static_cast<int>(pow(3, direction_enemy_stone_num) +
                                pow(3.3, direction_my_stone_num))) /
              // pow(3, direction_my_stone_num))) /
              direction_length_sum;
          score_map[column][row] -= (column - board.board_size() / 2) *
                                    (column - board.board_size() / 2);
          score_map[column][row] -=
              (row - board.board_size() / 2) * (row - board.board_size() / 2);
        }
      }
    }
  }
  return score_map;
}
