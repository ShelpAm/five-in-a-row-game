//
// Created by small-sheep on 11/11/22.
//

#include "board_coordinate.h"

BoardCoordinate::BoardCoordinate() {
}

BoardCoordinate::BoardCoordinate(const BoardCoordinate &board_coordinate)
: row(board_coordinate.row),
  column(board_coordinate.column) {
}

BoardCoordinate::BoardCoordinate(int row, int column)
: row(row), column(column) {
}
