#ifndef FIVE_IN_A_ROW_GAME_FIVE_IN_A_ROW_GAME_H
#define FIVE_IN_A_ROW_GAME_FIVE_IN_A_ROW_GAME_H

#include <cstddef>
#include <iostream>
#include <memory>
#include <stack>
#include <type_traits>

#include "five_in_a_row_game/player.h"

enum class GameState : unsigned int {
  kGameStateNotStarted,
  kGameStateStarted,
  kGameStateOver
};

template <typename T>
concept PlayerType = std::is_same_v<T, Player>;

/// @brief A particular match.
class FiveInARowGame {
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
    game_state_ = GameState::kGameStateStarted;
    std::cout << "[info] Game started.\n";
    Render();
  }

  void Tick();

  GameState game_state() const { return game_state_; }
  const Player * winner() { return winner_; }

 private:
  /// @brief Updates processes data
  void Update();
  void CurrentPlayerMove();
  void UpdateGameState();

  void Render() const;

  enum GameState game_state_ { GameState::kGameStateNotStarted };
  std::stack<Move> history_moves_;
  std::size_t num_of_moves_{0};
  Player *moving_player_{nullptr}, *unmoving_player_{nullptr};
  Player * winner_{nullptr};
  Board board_{9};
};

#endif  // FIVE_IN_A_ROW_GAME_FIVE_IN_A_ROW_GAME_H
