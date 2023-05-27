//
// Created by small-sheep on 11/10/22.
//

#include "five_in_a_row_game/easy_ai_player.h"

#include <math.h>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

#include "five_in_a_row_game/ai_player.h"
#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/stone_type.h"
#include "five_in_a_row_game/vector2d.h"
#include "glm/geometric.hpp"
#include "glm/glm.hpp"

EasyAIPlayer::EasyAIPlayer() {}

EasyAIPlayer::EasyAIPlayer(const AIPlayer * const ai_player)
    : AIPlayer(*ai_player) {}

EasyAIPlayer::~EasyAIPlayer() {}

const std::vector<BoardCoordinate> EasyAIPlayer::Think(
    const Board & board) const {
  auto score_map = CalculateScore(board);
  float current_maximum_score = 0;
  std::vector<BoardCoordinate> coordinates_of_maximum_score;

  int end = static_cast<int>(board.board_size());
  for (int column = 0; column != end; ++column) {
    for (int row = 0; row != end; ++row) {
      if (current_maximum_score < score_map[column][row]) {
        current_maximum_score = score_map[column][row];
        coordinates_of_maximum_score.clear();
        coordinates_of_maximum_score.push_back(BoardCoordinate(column, row));
      } else if (std::size_t(current_maximum_score) ==
                 std::size_t(score_map[column][row])) {
        coordinates_of_maximum_score.push_back(BoardCoordinate(column, row));
      }
    }
  }

  return coordinates_of_maximum_score;
}

const ScoreMapType EasyAIPlayer::CalculateScore(const Board & board) const {
  std::vector<float> empty_column(board.board_size(), 0.0f);
  ScoreMapType score_map(board.board_size(), empty_column);
  int end = static_cast<int>(board.board_size());
  for (int x = 0; x != end; ++x) {
    for (int y = 0; y != end; ++y) {
      if (board.GetStoneTypeInCoordinate(BoardCoordinate(x, y)) !=
          StoneType::kStoneTypeEmpty) {
        continue;
      }
      float score_buffer = 0;
      std::size_t num_of_all_my_stones = 0;
      std::size_t num_of_all_enemy_stones = 0;
      std::size_t num_of_all_empty_stone = 0;
      // for 8 certain directions
      Vector2D<int> directions[8] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                     {1, 0},   {-1, 1}, {0, 1},  {1, 1}};
      for (std::size_t i = 0; i < 8; ++i) {
        auto x_direction = directions[i].x();
        auto y_direction = directions[i].y();
        std::size_t num_of_curr_direction_enemy_stones = 0;
        std::size_t num_of_curr_direction_my_stones = 0;
        std::size_t sum_of_curr_direction_length = 1;
        // iterate from the second stone to the fifth stone
        for (int length_to_actual_coord = 1; length_to_actual_coord != 5;
             ++length_to_actual_coord) {
          const int absolute_x = x + x_direction * length_to_actual_coord;
          const int absolute_y = y + y_direction * length_to_actual_coord;
          const BoardCoordinate absolute_coordinate(absolute_x, absolute_y);
          if (!IsCoordinateInRangeOfBoard(absolute_coordinate, board)) {
            break;
          }
          const StoneType current_stone_type =
              board.GetStoneTypeInCoordinate(absolute_coordinate);
          if (current_stone_type == stone_type_) {
            ++num_of_curr_direction_my_stones;
            ++num_of_all_my_stones;
            sum_of_curr_direction_length += length_to_actual_coord;
          } else if (current_stone_type == StoneType::kStoneTypeEmpty) {
            ++num_of_all_empty_stone;
          } else {
            ++num_of_curr_direction_enemy_stones;
            ++num_of_all_enemy_stones;
            sum_of_curr_direction_length += length_to_actual_coord;
          }
        }
        score_buffer += (pow(2, num_of_curr_direction_enemy_stones) +
                         pow(2, num_of_curr_direction_my_stones)) /
                        sum_of_curr_direction_length;
        score_buffer +=
            pow(1.1f, int(num_of_all_my_stones + num_of_all_enemy_stones));
        score_buffer -= glm::distance(
            glm::vec2(x, y), glm::vec2(board.center().x(), board.center().y()));
        score_map[x][y] = score_buffer;
      }
    }
  }
  return score_map;
}
