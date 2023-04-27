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
#include "five_in_a_row_game/stone_type.h"

FiveInARowGame::FiveInARowGame() {}

FiveInARowGame::FiveInARowGame(const FiveInARowGame & other)
    : game_state_(other.game_state_),
      history_moves_(other.history_moves_),
      num_moves_(other.num_moves_),
      moving_player_(other.moving_player_),
      unmoving_player_(other.unmoving_player_),
      winner_(other.winner_),
      board_(other.board_) {}

FiveInARowGame & FiveInARowGame::operator=(const FiveInARowGame & other) {
  game_state_ = other.game_state_;
  history_moves_ = other.history_moves_;
  num_moves_ = other.num_moves_;
  moving_player_ = other.moving_player_;
  unmoving_player_ = other.unmoving_player_;
  winner_ = other.winner_;
  board_ = other.board_;
  return *this;
}

FiveInARowGame::~FiveInARowGame() {}

void FiveInARowGame::Tick() {
  Update();
  Render();
}

void FiveInARowGame::Update() {
  std::cout << "It's the turn of player '" << moving_player_->name() << "'.\n";
  CurrentPlayerMove();
  UpdateGameState();
}

void FiveInARowGame::Render() const {
  auto IsOdd = [](std::size_t num) -> bool {
    return static_cast<bool>(num % 2);
  };
  if (IsOdd(num_moves_)) {
    std::cout << "----------------------------------------\n"
              << "Round " << num_moves_ / 2 << "\n";
  }
  // Following is for debugging, which cannot be used for this scenario.
  // std::cout << *this;
  std::ostringstream buf;

  auto PrintLine1 = [this, &buf]() {
    buf << "+  " << ' ';
    for (std::size_t i = 0; i != board_.board_size(); ++i) {
      buf << i << ' ';
    }
    buf << "  +";
    buf << '\n';
  };
  auto PrintLine2 = [this, &buf]() {
    buf << "   " << std::string(board_.board_size() * 2 + 1, '-') << '\n';
  };

  buf << "-- The game map:\n";
  PrintLine1();
  PrintLine2();
  for (std::size_t row = 0; row != board_.board_size(); ++row) {
    buf << row << " | ";
    for (std::size_t column = 0; column != board_.board_size(); ++column) {
      char stone_code;
      if (!history_moves_.empty() &&
          BoardCoordinate{column, row} ==
              history_moves_.back().board_coordinate) {
        stone_code = 'L';
      } else {
        stone_code = stone_code_map().at(
            board_.GetStoneTypeInCoordinate(BoardCoordinate(column, row)));
      }
      buf << stone_code << " ";
    }
    buf << "| " << row << "\n";
  }
  PrintLine2();
  PrintLine1();
  std::cout << buf.str();
}

void FiveInARowGame::UpdateGameState() {
  if (IsWinning()) {
    winner_ = moving_player_;
    game_state_ = GameState::kGameStateStoped;
  } else if (IsDrawing()) {
    winner_ = nullptr;
    game_state_ = GameState::kGameStateStoped;
  }
  std::swap(moving_player_, unmoving_player_);
}

void FiveInARowGame::CurrentPlayerMove() {
  const ::Move move{moving_player_->Move(board_)};
  history_moves_.push_back(move);
  num_moves_++;
}

bool FiveInARowGame::IsWinning() const {
  // This fucntion needs only to check the latest move.
  const Move & last_move{history_moves_.back()};
  for (int vertical = 0; vertical != 2; ++vertical) {
    for (int horizontal = -1; horizontal != 2; ++horizontal) {
      // filter directions
      // all directions that should be checked:
      //   - - -
      //   - - +
      //   + + +
      if (vertical == 0 && horizontal != 1) {
        continue;
      }
      // for every group of five stones
      for (int offset = -4; offset != 1; ++offset) {
        int i = 0;
        // for every stone in the group
        for (; i != 5; ++i) {
          const auto & last_move_coordinate = last_move.board_coordinate;
          BoardCoordinate coord{
              last_move_coordinate.column() + horizontal * (offset + i),
              last_move_coordinate.row() + vertical * (offset + i)};
          if (!IsCoordinateInRangeOfBoard(coord, board_) ||
              board_.GetStoneTypeInCoordinate(coord) != last_move.stone_type) {
            break;
          }
        }
        if (i == 5) {
          return true;
        }
      }
    }
  }
  return false;
}

bool FiveInARowGame::IsDrawing() const {
  return num_moves_ == board_.board_size() * board_.board_size();
}

std::ostream & operator<<(std::ostream & os, const FiveInARowGame & game) {
  std::stringstream buf;
  buf << "FiveInARowGame {"
      << "\n  game_state_:" << game_state_string_map().at(game.game_state())
      << "\n  history_moves_:\n";
  for (const auto & move : game.history_moves()) {
    buf << move;
  }
  buf << "\n  num_moves_:" << game.num_moves()
      << "\n  moving_player_:" << game.moving_player()->name()
      << "\n  unmoving_player_:" << game.unmoving_player()->name()
      << "\n  board_:\n"
      << game.board() << "}\n";
  os << buf.str();
  return os;
}
