//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_BOARD_COORDINATE_H
#define FIVE_IN_A_ROW_GAME_SRC_BOARD_COORDINATE_H


class BoardCoordinate {
 public:
  BoardCoordinate();

  BoardCoordinate(const BoardCoordinate &board_coordinate);

  BoardCoordinate(int row, int column);

  int row = 0;
  int column = 0;
};


#endif //FIVE_IN_A_ROW_GAME_SRC_BOARD_COORDINATE_H
