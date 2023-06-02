#ifndef FIVE_IN_A_ROW_GAME_GAME_OBJECT_H
#define FIVE_IN_A_ROW_GAME_GAME_OBJECT_H

#include "glm/ext/vector_float3.hpp"

class GameObject {
 public:
  GameObject() = default;
  GameObject(GameObject &&) = delete;
  GameObject(const GameObject &) = delete;
  GameObject & operator=(GameObject &&) = delete;
  GameObject & operator=(const GameObject &) = delete;
  virtual ~GameObject() = default;

  virtual void Render() const = 0;
  virtual void Update() = 0;

  unsigned id() const { return id_; }
  const glm::vec3 & position() const { return position_; }

 private:
  unsigned id_;
  glm::vec3 position_;
};

#endif  // FIVE_IN_A_ROW_GAME_GAME_OBJECT_H
