//
// Created by small-sheep on 11/10/22.
//

#include "five_in_a_row_game/easy_ai_player.h"

#include <cmath>
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
  int max_score{0};
  std::vector<BoardCoordinate> coordinates;

  int end = board.BoardSize();
  for (int column = 0; column != end; ++column) {
    for (int row = 0; row != end; ++row) {
      if (!CoordinateIsInRangeOfBoard(BoardCoordinate{column, row}, board)) {
        continue;
      }
      if (max_score < score_map[column][row]) {
        max_score = score_map[column][row];
        coordinates.clear();
        coordinates.push_back(BoardCoordinate{column, row});
      } else if (max_score == score_map[column][row]) {
        coordinates.push_back(BoardCoordinate{column, row});
      }
    }
  }
  return coordinates;
}

const std::vector<std::vector<int>> EasyAIPlayer::CalculateScore(
    const Board & board) const {
  std::vector<std::vector<int>> score_map(
      board.BoardSize(), std::vector<int>(board.BoardSize(), 0));
  int end = board.BoardSize();
  for (int column = 0; column != end; ++column) {
    for (int row = 0; row != end; ++row) {
      if (board.StoneTypeInCoordinate(BoardCoordinate{column, row}) !=
          StoneType::kStoneTypeEmpty) {
        continue;
      }
      int my_stones = 0, enemy_stones = 0, empty_stones = 0;
      // 8 directions
      for (int horizontal = -1; horizontal != 2; ++horizontal) {
        for (int vertical = -1; vertical != 2; ++vertical) {
          if (horizontal == 0 && vertical == 0) {
            continue;
          }
          // Here starting calculating.
          for (int length = 1; length != 5; ++length) {
            int current_column{column + horizontal * length},
                current_row{row + vertical * length};
            const BoardCoordinate current_coordinate{current_column,
                                                     current_row};
            if (!CoordinateIsInRangeOfBoard(current_coordinate, board)) {
              break;
            }
            StoneType current_stone_type =
                board.StoneTypeInCoordinate(current_coordinate);
            if (current_stone_type == StoneTypeInUse()) {
              ++my_stones;
              score_map[column][row] += 20 / length;
            } else if (current_stone_type == StoneType::kStoneTypeEmpty) {
              ++empty_stones;
            } else {
              ++enemy_stones;
              score_map[column][row] += 20 / length;
            }
          }
        }
      }
      score_map[column][row] *= static_cast<int>(std::pow(2, my_stones + 1));
      score_map[column][row] *= static_cast<int>(std::pow(2, enemy_stones + 1));
      // score_map[column][row] += my_stones * 5;
      // score_map[column][row] += enemy_stones * 5;
    }
  }
  return score_map;
}
