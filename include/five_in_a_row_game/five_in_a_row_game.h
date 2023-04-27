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

enum class GameState : std::size_t {
  kGameStateNotStarted,
  kGameStateStarted,
  kGameStateStoped
};

inline const auto & game_state_string_map() {
  static std::map<GameState, std::string> game_state_string_map{
      {GameState::kGameStateNotStarted, "kGameStateNotStarted"},
      {GameState::kGameStateStarted, "kGameStateStarted"},
      {GameState::kGameStateStoped, "kGameStateStoped"}};
  return game_state_string_map;
}

template <typename T>
concept PlayerType = std::is_same_v<T, Player>;

/// @brief FiveInARowGame defines a particular match between two players, which
/// contains game state, winner, etc. . It can be in any state, ranging from
/// going on to having been over.
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
  const std::vector<Move> & history_moves() const { return history_moves_; }
  std::size_t num_moves() const { return num_moves_; }
  const Player * moving_player() const { return moving_player_; }
  const Player * unmoving_player() const { return unmoving_player_; }
  const Player * winner() const { return winner_; }
  const Board & board() const { return board_; }

 private:
  /// @brief Updates processes data
  void Update();
  void CurrentPlayerMove();
  void UpdateGameState();
  bool IsWinning() const;
  bool IsDrawing() const;

  void Render() const;

  GameState game_state_{GameState::kGameStateNotStarted};
  std::vector<Move> history_moves_{};
  std::size_t num_moves_{0};
  Player * moving_player_{nullptr};
  Player * unmoving_player_{nullptr};
  Player * winner_{nullptr};
  Board board_{6};
};

std::ostream & operator<<(std::ostream & os, const FiveInARowGame & game);

#endif  // FIVE_IN_A_ROW_GAME_FIVE_IN_A_ROW_GAME_H
