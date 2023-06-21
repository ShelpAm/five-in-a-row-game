#include <cassert>
#include <iostream>

#include "five_in_a_row_game/ai_player.h"
#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/logger.h"
#include "five_in_a_row_game/vector2d.h"

int main(int argc, const char ** argv) {
  // test board_coordinate.h
  BoardCoordinate board_coordinate;

  // Testing vector2d.h
  Vector2D<int> a(1, 2);
  Vector2D<int> b(3, 4);
  b = a;
  assert(b == a);
  b = Vector2D<int>();

  std::map<BoardCoordinate, int> map;

  map.insert_or_assign(a, 2);
  map.insert_or_assign(b, 6);
  assert(map[a] == 2);
  assert(map[b] == 6);

  Logger::instance().Log("All tests passed.");
  return 0;
}
