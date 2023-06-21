//
// Created by small-sheep on 11/10/22.
//

#ifndef FIVE_IN_A_ROW_GAME_EASY_AI_PLAYER_H
#define FIVE_IN_A_ROW_GAME_EASY_AI_PLAYER_H

#include <math.h>

#include <cstddef>
#include <vector>

#include "ai_player.h"
#include "easy_ai_player_fwd.h"
#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/board_fwd.h"
#include "five_in_a_row_game/game_board.h"
#include "five_in_a_row_game/player.h"
#include "five_in_a_row_game/vector2d.h"

struct CalculationResult {
  CalculationResult operator+(const CalculationResult & other) const {
    return CalculationResult{
        score + other.score,
        count_of_all_my_pieces + other.count_of_all_my_pieces,
        count_of_all_empty_pieces + other.count_of_all_empty_pieces,
        count_of_all_enemy_pieces + other.count_of_all_enemy_pieces};
  }
  CalculationResult & operator+=(const CalculationResult & other) {
    *this = *this + other;
    return *this;
  }
  float score = 0.0;
  int count_of_all_my_pieces = 0;
  int count_of_all_empty_pieces = 0;
  int count_of_all_enemy_pieces = 0;
};

class EasyAIPlayer : public AIPlayer {
 public:
  EasyAIPlayer() = default;
  virtual ~EasyAIPlayer() override;

  virtual const ScoreMap CalculateScores(
      const GameBoard & board) const override;

  CalculationResult CalculateScoreFromSecondToFifthInCertainDirection(
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
};

#endif  // FIVE_IN_A_ROW_GAME_EASY_AI_PLAYER_H
