#ifndef FIVE_IN_A_ROW_GAME_FIVE_IN_A_ROW_GAME_H
#define FIVE_IN_A_ROW_GAME_FIVE_IN_A_ROW_GAME_H

#include <iostream>
#include <memory>
#include <stack>
#include <type_traits>

#include "five_in_a_row_game/player.h"

enum class GameState : int { kStateNotStarted, kStateStarted, kStateOver };

template <typename T>
concept PlayerType = std::is_same_v<T, Player>;

/// @brief A particular match.
class FiveInARowGame {
 public:
  FiveInARowGame();

  void ClearBoard();

  /// @brief Starts the game and begin the game loop.
  /// @param first_player - The first player
  /// @param later_player - The second player
  template <PlayerType T> void Start(T & first_player, T & later_player) {
    moving_player_ = &first_player;
    unmoving_player_ = &later_player;

    moving_player_->SetStoneTypeInUse(StoneType::kStoneTypeBlack);
    unmoving_player_->SetStoneTypeInUse(StoneType::kStoneTypeWhite);

    // println("Game starts.");
    std::cout << "Game starts.\n";
    game_state_ = GameState::kStateStarted;
    Render();
  }

  void Tick();

  GameState GameState() const { return game_state_; }
  const Player * Winner() { return winner_; }

 private:
  /// @brief Updates processes data
  void Update();
  void CurrentPlayerMove();
  void UpdateStatus();

  void Render() const;

  enum GameState game_state_ { GameState::kStateNotStarted };
  std::stack<Move> move_histories_;
  Player *moving_player_{nullptr}, *unmoving_player_{nullptr};
  Player * winner_{nullptr};
  Board board_{9};
};

#endif // FIVE_IN_A_ROW_GAME_FIVE_IN_A_ROW_GAME_H
