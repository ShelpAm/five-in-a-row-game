//
// Created by small-sheep on 11/10/22.
//

#include "five_in_a_row_game/easy_ai_player.h"

#include <math.h>

#include <algorithm>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include "five_in_a_row_game/ai_player.h"
#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/logger.h"
#include "five_in_a_row_game/player.h"
#include "five_in_a_row_game/stone_type.h"
#include "five_in_a_row_game/vector2d.h"
#include "glm/geometric.hpp"
#include "glm/glm.hpp"

EasyAIPlayer::~EasyAIPlayer() {}

const ScoreMap EasyAIPlayer::CalculateScoreMap(const GameBoard & board) const {
  ScoreMap result;  // It only contains the coordinates that can be placed piece
  // Predefined as they shouldn't be initialized too many times.
  const Vector2D<int> directions[8]{{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                    {1, 0},   {-1, 1}, {0, 1},  {1, 1}};
  for (int x = 0; x != board.board_size(); ++x) {
    for (int y = 0; y != board.board_size(); ++y) {
      if (board.stone_type_by_coordinate(Vector2D<int>(x, y)) !=
          StoneType::kStoneTypeEmpty) {
        continue;
      }
      CalculationResult piece_result;
      const Vector2D<int> piece_coordinate(x, y);
      for (const auto & direction : directions) {
        auto result_in_direction =
            CalculateScoreInDirection(board, piece_coordinate, direction);
        piece_result += result_in_direction;
      }
      piece_result.score +=
          pow(1.1f, piece_result.count_of_all_my_pieces +
                        piece_result.count_of_all_enemy_pieces);
      piece_result.score -= glm::distance(
          glm::vec2(x, y), glm::vec2(board.center().x(), board.center().y()));
      result.insert_or_assign(piece_coordinate, piece_result.score);
    }
  }
  return result;
}
CalculationResult EasyAIPlayer::CalculateScoreInDirection(
    const GameBoard & board, const Vector2D<int> & curr_coord,
    const Vector2D<int> & curr_direction) const {
  CalculationResult result;
  auto num_of_curr_direction_enemy_stones = 0;
  auto num_of_curr_direction_my_stones = 0;
  auto sum_of_curr_direction_length = 1;
  for (int length_to_actual_coord = 1; length_to_actual_coord != 5;
       ++length_to_actual_coord) {
    const auto actual_coord =
        curr_coord + curr_direction * length_to_actual_coord;
    if (!board.contains(actual_coord)) {
      return result;
    }
    const StoneType curr_stone_type =
        board.stone_type_by_coordinate(actual_coord);
    if (curr_stone_type == stone_type_) {
      ++num_of_curr_direction_my_stones;
      ++result.count_of_all_my_pieces;
      sum_of_curr_direction_length += length_to_actual_coord;
    } else if (curr_stone_type == StoneType::kStoneTypeEmpty) {
      ++result.count_of_all_empty_pieces;
    } else {
      ++num_of_curr_direction_enemy_stones;
      ++result.count_of_all_enemy_pieces;
      sum_of_curr_direction_length += length_to_actual_coord;
    }
  }
  result.score += (pow(2, num_of_curr_direction_enemy_stones) +
                   pow(2, num_of_curr_direction_my_stones)) /
                  sum_of_curr_direction_length;
  return result;
}
CalculationResult & CalculationResult::operator+=(
    const CalculationResult & other) {
  *this = *this + other;
  return *this;
}
CalculationResult CalculationResult::operator+(
    const CalculationResult & other) const {
  return CalculationResult{
      score + other.score,
      count_of_all_my_pieces + other.count_of_all_my_pieces,
      count_of_all_empty_pieces + other.count_of_all_empty_pieces,
      count_of_all_enemy_pieces + other.count_of_all_enemy_pieces};
}

EasyAIPlayer::EasyAIPlayer(const int id, const char * name) {
  set_id(id);
  set_name(name);
}
