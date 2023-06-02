#ifndef FIVE_IN_A_ROW_GAME_GAME_OBJECT_SELECTOR_H
#define FIVE_IN_A_ROW_GAME_GAME_OBJECT_SELECTOR_H

#include "five_in_a_row_game/vector2d.h"

class GameObject;

class GameObjectSelector {
 public:
  GameObjectSelector() = default;
  GameObjectSelector(GameObjectSelector &&) = delete;
  GameObjectSelector(const GameObjectSelector &) = delete;
  GameObjectSelector & operator=(GameObjectSelector &&) = delete;
  GameObjectSelector & operator=(const GameObjectSelector &) = delete;
  ~GameObjectSelector() = default;

  GameObject * SelectAt(const Vector2D<float> & position) const;

 private:
};

#endif  // FIVE_IN_A_ROW_GAME_GAME_OBJECT_SELECTOR_H
