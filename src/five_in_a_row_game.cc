#include "five_in_a_row_game/five_in_a_row_game.h"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "five_in_a_row_game/board.h"
#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/move.h"
#include "five_in_a_row_game/stone_type.h"

FiveInARowGame::FiveInARowGame() {}

FiveInARowGame::FiveInARowGame(const FiveInARowGame & other)
    : game_state_(other.game_state_),
      history_moves_(other.history_moves_),
      num_of_moves_(other.num_of_moves_),
      moving_player_(other.moving_player_),
      unmoving_player_(other.unmoving_player_),
      winner_(other.winner_),
      board_(other.board_) {}

FiveInARowGame & FiveInARowGame::operator=(const FiveInARowGame & other) {
  game_state_ = other.game_state_;
  history_moves_ = other.history_moves_;
  num_of_moves_ = other.num_of_moves_;
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
  std::swap(moving_player_, unmoving_player_);
}

void FiveInARowGame::Render() const {
  // Do some cleaning.
  std::ostringstream buf;

  auto IsOdd = [](std::size_t num) -> bool {
    return static_cast<bool>(num % 2);
  };

  if (IsOdd(num_of_moves_)) {
    buf << "----------------------------------------\n"
        << "Round " << num_of_moves_ / 2 << "\n";
  }
  buf << "-- The game map:\n";
  auto PrintLine1 = [this, &buf]() {
    buf << "+  " << ' ';
    for (std::size_t i = 0; i != board_.BoardSize(); ++i) {
      buf << i << ' ';
    }
    buf << "  +";
    buf << '\n';
  };
  auto PrintLine2 = [this, &buf]() {
    buf << "   " << std::string(board_.BoardSize() * 2 + 1, '-') << '\n';
  };
  PrintLine1();
  PrintLine2();
  for (std::size_t row = 0; row != board_.BoardSize(); ++row) {
    buf << row << " | ";
    for (std::size_t column = 0; column != board_.BoardSize(); ++column) {
      if (!history_moves_.empty() &&
          BoardCoordinate{column, row} ==
              history_moves_.top().board_coordinate) {
        buf << "L ";

      } else {
        buf << static_cast<int>(
                   board_.StoneTypeInCoordinate(BoardCoordinate{column, row}))
            << " ";
      }
    }
    buf << "| " << row << "\n";
  }
  PrintLine2();
  PrintLine1();
  std::cout << buf.str();
}

void FiveInARowGame::UpdateGameState() {
  auto Winning = [](const Board & board, const Move & last_move) -> bool {
    // This only need to check the latest move.
    // Directions: - - -
    //             - - +
    //             + + +
    for (int vertical = 0; vertical != 2; ++vertical) {
      for (int horizontal = -1; horizontal != 2; ++horizontal) {
        if (vertical == 0 && horizontal != 1) {
          continue;
        }
        // for every five stones
        for (int distance = -4; distance != 1; ++distance) {
          // for every stone
          // The definition of i is here, so the "i" can be accessed out of
          //  the for-block(line94)
          int i = 0;
          for (; i != 5; ++i) {
            const BoardCoordinate & last_move_coordinate =
                last_move.board_coordinate;
            BoardCoordinate c{
                last_move_coordinate.Column() + horizontal * (distance + i),
                last_move_coordinate.Row() + vertical * (distance + i)};
            if (!CoordinateIsInRangeOfBoard(c, board) ||
                board.StoneTypeInCoordinate(c) != last_move.stone_type) {
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
  };

  // two players 平局
  auto Drawing = [](const Board & board) -> bool {
    for (const auto & i : board.GetStoneTypeMap()) {
      for (const auto & j : i) {
        if (j == StoneType::kStoneTypeEmpty) {
          return false;
        }
      }
    }
    return true;
  };

  const Move & last_move = history_moves_.top();
  if (Winning(board_, last_move)) {
    winner_ = moving_player_;
    game_state_ = GameState::kGameStateOver;
  } else if (Drawing(board_)) {
    winner_ = nullptr;
    game_state_ = GameState::kGameStateOver;
  }
}

void FiveInARowGame::CurrentPlayerMove() {
  const ::Move move{moving_player_->Move(board_)};
  history_moves_.push(move);
  num_of_moves_++;
}
