#include "five_in_a_row_game/five_in_a_row_game.h"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

#include "five_in_a_row_game/board.h"
#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/move.h"
#include "five_in_a_row_game/state.h"
#include "five_in_a_row_game/stone_type.h"

FiveInARowGame::FiveInARowGame(const FiveInARowGame & other)
    : state_(other.state_),
      moving_player_(other.moving_player_),
      unmoving_player_(other.unmoving_player_),
      winner_(other.winner_),
      board_(other.board_) {}

FiveInARowGame & FiveInARowGame::operator=(const FiveInARowGame & other) {
  state_ = other.state_;
  moving_player_ = other.moving_player_;
  unmoving_player_ = other.unmoving_player_;
  winner_ = other.winner_;
  board_ = other.board_;
  return *this;
}

FiveInARowGame::~FiveInARowGame() {}

void FiveInARowGame::Update() {
  switch (state_) {
    case State::kStateNotStarted:
      break;
    case State::kStateStarted:
      moving_player_->Move(board_);
      switch (board_.GetBoardState()) {
        case BoardState::kBoardStateWinning:
          winner_ = moving_player_;
          state_ = State::kStateEnded;
          break;
        case BoardState::kBoardStateDrawing:
          winner_ = nullptr;
          state_ = State::kStateEnded;
          break;
        case BoardState::kBoardStateStarted:
          state_ = State::kStateStarted;
          break;
      }
      std::swap(moving_player_, unmoving_player_);
      break;
    case State::kStateStoped:
      break;
    case State::kStateEnded:
      break;
  }
}

void FiveInARowGame::Render() const {
  switch (state_) {
    case State::kStateNotStarted:
      break;
    case State::kStateStarted:
      std::cout << "------- The " << board_.num_moves() << " move -------\n"
                << board_;
      break;
    case State::kStateStoped:
      break;
    case State::kStateEnded:
      std::cout << "------- The " << board_.num_moves() << " move -------\n"
                << board_;
      if (winner_) {
        std::cout << "Game over! The winner is " << winner_->name() << '\n';
      } else {
        std::cout << "Game draws! No one wins!\n";
      }
      break;
  }
}

std::ostream & operator<<(std::ostream & os, const FiveInARowGame & game) {
  std::stringstream buf;
  buf << "FiveInARowGame {"
      << "\n  game_state_:" << state_string_map().at(game.state_)
      << "\n  num_moves_:" << game.board_.num_moves()
      << "\n  moving_player_:" << game.moving_player_->name()
      << "\n  unmoving_player_:" << game.unmoving_player_->name()
      << "\n  board_:\n"
      << game.board_ << "}\n";
  os << buf.str();
  return os;
}
