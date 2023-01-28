#ifndef FIVE_IN_A_ROW_GAME_INCLUDE_FIVE_IN_A_ROW_GAME_H
#define FIVE_IN_A_ROW_GAME_INCLUDE_FIVE_IN_A_ROW_GAME_H

#include <memory>
#include <stack>
#include <string>

#include "five_in_a_row_game/move.h"
#include "five_in_a_row_game/player.h"

/// @brief A particular match.
class FiveInARowGame {
 public:
  FiveInARowGame();

  /// @brief Starts the game and begin the game loop.
  /// @param first_hand_player - The first player
  /// @param second_hand_player - The second player
  void Start(Player *first_hand_player, Player *second_hand_player);

  void Tick();

  bool Started() const { return started_; }
  void SetStarted(bool started) { started_ = started; }
  bool Over() const { return over_; }
  void SetOver(bool over) { over_ = over; }
  const Player *Winner() { return winner_; }

 private:
  /// @brief Updates processes data
  void Update();
  void CurrentPlayerMove();
  void UpdateStatus();

  void Render() const;

  bool started_ = false, over_ = false;
  std::stack<Move> history_moves_;
  Player *moving_player_, *unmoving_player_;
  Player *winner_;
  std::unique_ptr<Board> board_pointer_;
  Player *players_[2];
};

#endif  // FIVE_IN_A_ROW_GAME_INCLUDE_FIVE_IN_A_ROW_GAME_H
