//
// Created by small-sheep on 11/10/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_PLAYER_H
#define FIVE_IN_A_ROW_GAME_SRC_PLAYER_H

#include <five_in_a_row_game/board.h>
#include <five_in_a_row_game/board_coordinate.h>

class Player {
 public:
  Player();

  explicit Player(StoneType used_stone_type);

  virtual ~Player();

  virtual const BoardCoordinate Think(const Board *board_ptr) const = 0;

  void PlaceAStone(Board *board_ptr,
                   const BoardCoordinate &board_coordinate) const;

  void ThinkAndPlaceAStone(Board *board_ptr) const;

  StoneType UsedStoneType() const;

  void SetUsedStoneType(StoneType used_stone_type);

 private:
  StoneType used_stone_type_;
};

#endif  // FIVE_IN_A_ROW_GAME_SRC_PLAYER_H
