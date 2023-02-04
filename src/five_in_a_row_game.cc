#include "five_in_a_row_game/five_in_a_row_game.h"

#include <sstream>

#include "five_in_a_row_game/board.h"
#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/move.h"
#include "five_in_a_row_game/stone_type.h"

FiveInARowGame::FiveInARowGame() : board_(Board(9)) {}

void FiveInARowGame::ClearBoard() { board_ = Board{9}; }

void FiveInARowGame::Tick() {
  Update();
  Render();
}

void FiveInARowGame::Update() {
  CurrentPlayerMove();
  UpdateStatus();
  std::swap(moving_player_, unmoving_player_);
}

void FiveInARowGame::Render() const {
  // Do some cleaning.
  std::ostringstream buf;

  buf << "The game map:\n";
  auto PrintLine1 = [this, &buf]() {
    buf << "+  " << ' ';
    for (int i = 0; i != board_.BoardSize(); ++i) {
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
  for (int row = 0; row != board_.BoardSize(); ++row) {
    buf << row << " | ";
    for (int column = 0; column != board_.BoardSize(); ++column) {
      buf << static_cast<int>(
                 board_.StoneTypeInCoordinate(BoardCoordinate{column, row}))
          << " ";
    }
    buf << "| " << row << "\n";
  }
  PrintLine2();
  PrintLine1();
  std::cout << buf.str();
}

void FiveInARowGame::UpdateStatus() {
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
          //  the for-block(line109)
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
    for (const auto & i : board.StoneTypeMap()) {
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
    SetStarted(false);
    SetOver(true);
  } else if (Drawing(board_)) {
    winner_ = nullptr;
    SetStarted(false);
    SetOver(true);
  }
}

void FiveInARowGame::CurrentPlayerMove() {
  const Move move{moving_player_->Move(board_)};
  history_moves_.push(move);
}
