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
#include "five_in_a_row_game/state.h"
#include "five_in_a_row_game/texture.h"
#include "shader_program.h"

template <typename T>
concept PlayerType = std::is_same_v<T, Player>;

/// @brief FiveInARowGame defines a particular match between two players, which
/// contains game state, winner, etc. . It can be in any state, ranging from
/// going on to having been over.
class FiveInARowGame {
  friend std::ostream & operator<<(std::ostream & os,
                                   const FiveInARowGame & game);

 public:
  // template <PlayerType T>
  FiveInARowGame(Player * black_player, Player * white_player) {
    black_player_ = moving_player_ = black_player;
    white_player_ = unmoving_player_ = white_player;
    moving_player_->set_stone_type_in_use(StoneType::kStoneTypeBlack);
    unmoving_player_->set_stone_type_in_use(StoneType::kStoneTypeWhite);
  }
  FiveInARowGame(const FiveInARowGame & other);
  FiveInARowGame & operator=(const FiveInARowGame & other);
  ~FiveInARowGame();

  /// @brief Starts the game.
  /// @param first_player - The first player
  /// @param later_player - The second player
  void Start() {
    state_ = State::kStateStarted;
    std::cout << "FiveInARowGame::Start Game started.\n";
    // Render();
  }
  /// @brief Updates processes data
  void Update();
  void Render(const ShaderProgram &) const;

 private:
  Texture2D diffuse_map_white{"white.png"};
  Texture2D diffuse_map_black{"black.png"};
  Texture2D diffuse_map{"container2.png"};
  Texture2D specular_map{"container2_specular.png"};
  State state_{State::kStateNotStarted};
  Player * moving_player_;
  Player * unmoving_player_;
  Player * black_player_;
  Player * white_player_;
  Player * winner_{nullptr};
  Board board_{35};
};

std::ostream & operator<<(std::ostream & os, const FiveInARowGame & game);

#endif  // FIVE_IN_A_ROW_GAME_FIVE_IN_A_ROW_GAME_H
