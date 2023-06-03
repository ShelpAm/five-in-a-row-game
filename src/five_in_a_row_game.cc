#include "five_in_a_row_game/five_in_a_row_game.h"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

#include "GLFW/glfw3.h"
#include "five_in_a_row_game/board.h"
#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/move.h"
#include "five_in_a_row_game/shader_program.h"
#include "five_in_a_row_game/state.h"
#include "five_in_a_row_game/stone_type.h"
#include "glad/gl.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float4.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/matrix.hpp"

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

void FiveInARowGame::Render(const ShaderProgram & shader_program) const {
  for (std::size_t i = 0; i != board_.board_size(); i++) {
    for (std::size_t j = 0; j != board_.board_size(); j++) {
      glm::mat4 model = glm::mat4(1.0f);
      // model = glm::translate(model, glm::vec3(i - 3, j - 3, 0.0f) - 1.0f);
      shader_program.SetMatrix4("model", model);
      shader_program.SetMatrix4("transposed_and_inverse_model",
                                glm::transpose(glm::inverse(model)));
      // TODO change to this
      // shader_program.SetTransposedMatrix4("transposed_and_inverse_model",
      // glm::inverse(model));
      if (board_.GetStoneTypeInCoordinate(BoardCoordinate(i, j)) ==
          StoneType::kStoneTypeBlack) {
        diffuse_map_black.Bind(shader_program, "material.diffuse_sampler", 0);
        specular_map.Bind(shader_program, "material.specular_sampler", 1);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
      } else if (board_.GetStoneTypeInCoordinate(BoardCoordinate(i, j)) ==
                 StoneType::kStoneTypeWhite) {
        diffuse_map_white.Bind(shader_program, "material.diffuse_sampler", 0);
        specular_map.Bind(shader_program, "material.specular_sampler", 1);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
      }
    }
  }
  switch (state_) {
    case State::kStateNotStarted:
      break;
    case State::kStateStarted:
      // std::cout << "------- The " << board_.num_moves() << " move -------\n"
      //           << board_;
      break;
    case State::kStateStoped:
      break;
    case State::kStateEnded:
      // std::cout << "------- The " << board_.num_moves() << " move -------\n"
      //           << board_;
      // if (winner_) {
      //   std::cout << "Game over! The winner is " << winner_->name() << '\n';
      // } else {
      //   std::cout << "Game draws! No one wins!\n";
      // }
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
