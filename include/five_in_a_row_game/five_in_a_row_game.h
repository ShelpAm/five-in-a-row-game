#ifndef FIVE_IN_A_ROW_GAME_FIVE_IN_A_ROW_GAME_HPP
#define FIVE_IN_A_ROW_GAME_FIVE_IN_A_ROW_GAME_HPP

#include <iostream>
#include <memory>
#include <stack>
#include <type_traits>

#include "five_in_a_row_game/player.h"

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
  template <PlayerType T>
  void Start(T & first_player, T & later_player) {
    moving_player_ = &first_player;
    unmoving_player_ = &later_player;

    moving_player_->SetStoneTypeInUse(StoneType::kStoneTypeBlack);
    unmoving_player_->SetStoneTypeInUse(StoneType::kStoneTypeWhite);

    // println("Game starts.");
    std::cout << "Game starts.\n";
    is_started_ = true;
    is_over_ = false;
    Render();
  }

  void Tick();

  bool IsStarted() const { return is_started_; }
  bool IsOver() const { return is_over_; }
  const Player * Winner() { return winner_; }

 private:
  /// @brief Updates processes data
  void Update();
  void CurrentPlayerMove();
  void UpdateStatus();

  void Render() const;

  bool is_started_ = false, is_over_ = false;
  std::stack<Move> move_histories_;
  Player *moving_player_{nullptr}, *unmoving_player_{nullptr};
  Player * winner_{nullptr};
  Board board_{9};
};

#endif  // FIVE_IN_A_ROW_GAME_FIVE_IN_A_ROW_GAME_HPP
