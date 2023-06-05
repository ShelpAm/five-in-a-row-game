#ifndef FIVE_IN_A_ROW_GAME_FIVE_IN_A_ROW_GAME_H
#define FIVE_IN_A_ROW_GAME_FIVE_IN_A_ROW_GAME_H

#include <cstddef>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <string>
#include <vector>

#include "five_in_a_row_game/board_fwd.h"
#include "five_in_a_row_game/move.h"
#include "five_in_a_row_game/player.h"
#include "five_in_a_row_game/shader_program.h"
#include "five_in_a_row_game/state.h"
#include "five_in_a_row_game/stone_type.h"
#include "five_in_a_row_game/texture2d.h"

template <typename T>
concept PlayerType = std::is_same_v<T, Player>;

/// @brief FiveInARowGame defines a particular match between two players, which
/// contains game state, winner, etc. . It can be in any state, ranging from
/// going on to having been over.
class FiveInARowGame {
  friend std::ostream & operator<<(std::ostream & os,
                                   const FiveInARowGame & game);

 public:
  FiveInARowGame() = delete;
  // template <PlayerType T>
  FiveInARowGame(Player * black_player, Player * white_player);
  FiveInARowGame(FiveInARowGame && other);
  FiveInARowGame(const FiveInARowGame & other);
  FiveInARowGame & operator=(FiveInARowGame && other);
  FiveInARowGame & operator=(const FiveInARowGame & other);
  ~FiveInARowGame();

  /// @brief Starts the game.
  void Start();

  /// @brief Updates processes data.
  void Update();

  /// @brief Renders the game.
  void Render(const ShaderProgram &) const;

 private:
  static Texture2D & GetStoneTextureByStoneType(const StoneType stone_type);

 private:
  Texture2D diffuse_map{"container2.png"};
  Texture2D specular_map{"container2_specular.png"};
  State state_{State::kStateNotStarted};
  Player * moving_player_;
  Player * unmoving_player_;
  Player * black_player_;
  Player * white_player_;
  Player * winner_{nullptr};
  GameBoard board_{9};
};

std::ostream & operator<<(std::ostream & os, const FiveInARowGame & game);

#endif  // FIVE_IN_A_ROW_GAME_FIVE_IN_A_ROW_GAME_H
