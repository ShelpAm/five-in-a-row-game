//
// Created by small-sheep on 11/10/22.
//

#include "five_in_a_row_game/ai_player.h"

#include "five_in_a_row_game/player.h"

AIPlayer::~AIPlayer() {}

const BoardCoordinateContainer AIPlayer::Think(const GameBoard & board) const {
  const auto score_map = CalculateScores(board);
  const auto max_score_coordinates = SelectMaxScoreCoordinatesFrom(score_map);
  return max_score_coordinates;
}

const BoardCoordinateContainer AIPlayer::SelectMaxScoreCoordinatesFrom(
    const ScoreMap & score_map) const {
  BoardCoordinateContainer result;
  float current_max_score = 0;
  for (const auto & i : score_map) {
    const auto & current_coordinate = i.first;
    const auto & current_score = i.second;
    if (current_max_score < current_score) {
      current_max_score = current_score;
      result.clear();
      result.push_back(current_coordinate);
    } else if (static_cast<int>((current_max_score)) ==
               static_cast<int>(current_score)) {
      result.push_back(current_coordinate);
    }
  }
  return result;
}
