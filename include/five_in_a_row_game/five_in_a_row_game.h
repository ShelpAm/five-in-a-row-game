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

enum class GameState : std::size_t {
  kGameStateNotStarted,
  kGameStateStarted,
  kGameStateStoped
};

template <typename T>
concept PlayerType = std::is_same_v<T, Player>;

/// @brief FiveInARowGame defines a particular match between two players, which
/// contains game state, winner, etc. . It can be in any state, ranging from
/// going on to having been over.
class FiveInARowGame {
  friend std::ostream & operator<<(std::ostream & os,
                                   const FiveInARowGame & game);

 public:
  FiveInARowGame();

  FiveInARowGame(const FiveInARowGame & other);

  FiveInARowGame & operator=(const FiveInARowGame & other);

  ~FiveInARowGame();

  /// @brief Starts the game and begin the game loop.
  /// @param first_player - The first player
  /// @param later_player - The second player
  template <PlayerType T>
  void Start(T & first_player, T & later_player) {
    moving_player_ = &first_player;
    unmoving_player_ = &later_player;
    moving_player_->set_stone_type_in_use(StoneType::kStoneTypeBlack);
    unmoving_player_->set_stone_type_in_use(StoneType::kStoneTypeWhite);
    state_ = State::kStateStarted;
    std::cout << "[Info] Game started.\n";
    Render();
  }

  /// @brief Updates processes data
  void Update();

  void Render() const;

  const Player * moving_player() const { return moving_player_; }
  const Player * unmoving_player() const { return unmoving_player_; }
  const Player * winner() const { return winner_; }
  const Board & board() const { return board_; }

 private:
  void CurrentPlayerMove();
  void UpdateGameState();

  State state_{State::kStateNotStarted};
  Player * moving_player_{nullptr};
  Player * unmoving_player_{nullptr};
  Player * winner_{nullptr};
  Board board_{6};
};

std::ostream & operator<<(std::ostream & os, const FiveInARowGame & game);

#endif  // FIVE_IN_A_ROW_GAME_FIVE_IN_A_ROW_GAME_H
