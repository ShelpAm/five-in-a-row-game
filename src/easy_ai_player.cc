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

const ScoreMap EasyAIPlayer::CalculateScores(const GameBoard & board) const {
  ScoreMap result_score_map;  // This only contains the coordinates which has a
                              // score.
  for (int x = 0; x != board.board_size(); ++x) {
    for (int y = 0; y != board.board_size(); ++y) {
      if (board.stone_type_by_coordinate(Vector2D<int>(x, y)) !=
          StoneType::kStoneTypeEmpty) {
        continue;
      }
      CalculationResult curr_result;
      Vector2D<int> curr_coord(x, y);
      // for 8 certain directions
      const Vector2D<int> directions[8]{{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                        {1, 0},   {-1, 1}, {0, 1},  {1, 1}};
      // for (int i = 0; i != 8; ++i) {
      for (const auto direction : directions) {
        // iterate from the second stone to the fifth stone
        auto result_in_certain_direction =
            CalculateScoreFromSecondToFifthInCertainDirection(board, curr_coord,
                                                              direction);
        curr_result += result_in_certain_direction;
        std::cout << "Three of result"
                  << " " << result_in_certain_direction.count_of_all_my_pieces
                  << " "
                  << result_in_certain_direction.count_of_all_empty_pieces
                  << " "
                  << result_in_certain_direction.count_of_all_enemy_pieces
                  << "\n";
      }
      curr_result.score += pow(1.1f, curr_result.count_of_all_my_pieces +
                                         curr_result.count_of_all_enemy_pieces);
      curr_result.score -= glm::distance(
          glm::vec2(x, y), glm::vec2(board.center().x(), board.center().y()));
      result_score_map.insert_or_assign(curr_coord, curr_result.score);
    }
  }
  return result_score_map;
}
