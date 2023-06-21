#include "five_in_a_row_game/five_in_a_row_game.h"

#include <unistd.h>

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

#include "GLFW/glfw3.h"
#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/game_board.h"
#include "five_in_a_row_game/move.h"
#include "five_in_a_row_game/shader_program.h"
#include "five_in_a_row_game/state.h"
#include "five_in_a_row_game/stone_type.h"
#include "five_in_a_row_game/texture2d.h"
#include "glad/gl.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float4.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/matrix.hpp"

// FiveInARowGame::FiveInARowGame(const FiveInARowGame & other)
//     : state_(other.state_),
//       moving_player_(other.moving_player_),
//       unmoving_player_(other.unmoving_player_),
//       winner_(other.winner_),
//       board_(other.board_) {}

// FiveInARowGame & FiveInARowGame::operator=(const FiveInARowGame & other) {
//   state_ = other.state_;
//   moving_player_ = other.moving_player_;
//   unmoving_player_ = other.unmoving_player_;
//   winner_ = other.winner_;
//   board_ = other.board_;
//   return *this;
// }

FiveInARowGame::~FiveInARowGame() {}

void FiveInARowGame::Update() {
  switch (state_) {
    case State::kStateNotStarted:
      break;
    case State::kStateStarted:
      OnGameStartedUpdate();
      break;
    case State::kStateStoped:
      break;
    case State::kStateEnded:
      break;
  }
}

void FiveInARowGame::Render(const ShaderProgram & shader_program) const {
  switch (state_) {
    case State::kStateNotStarted:
      break;
    case State::kStateStoped:
      // TODO: draw the `stopping` string.
      // SomeCodeDrawingStoppingString();
    case State::kStateStarted:
    case State::kStateEnded:
      RenderPieces(shader_program);
      break;
  }
  // printf("FiveInARowGame::Render invoked\n");
}

std::ostream & operator<<(std::ostream & os, const FiveInARowGame & game) {
  std::stringstream buf;
  buf << "FiveInARowGame {"
      << "\n  game_state_:" << state_string_map().at(game.state_)
      << "\n  num_moves_:" << game.board_.history_moves().size()
      << "\n  moving_player_:" << game.moving_player_->name()
      << "\n  unmoving_player_:" << game.unmoving_player_->name()
      << "\n  board_:\n"
      << game.board_ << "}\n";
  os << buf.str();
  return os;
}
void FiveInARowGame::Start() {
  state_ = State::kStateStarted;
  std::cout << "FiveInARowGame::Start Game started.\n";
}

Texture2D & FiveInARowGame::stone_texture_by_stone_type(
    const StoneType stone_type) {
  static Texture2D stone_textures[2]{Texture2D("black.png"),
                                     Texture2D{"white.png"}};
  static std::map<StoneType, Texture2D &> stone_type_to_texture_map{
      {StoneType::kStoneTypeBlack, stone_textures[0]},
      {StoneType::kStoneTypeWhite, stone_textures[1]}};
  return stone_type_to_texture_map.at(stone_type);
}

FiveInARowGame::FiveInARowGame(Player * black_player, Player * white_player) {
  black_player_ = moving_player_ = black_player;
  white_player_ = unmoving_player_ = white_player;
  moving_player_->set_stone_type(StoneType::kStoneTypeBlack);
  unmoving_player_->set_stone_type(StoneType::kStoneTypeWhite);
}
void FiveInARowGame::OnGameStartedUpdate() {
  moving_player_->Move(board_);
  switch (board_.board_state()) {
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
  std::cout << "board state: " << string_by_board_state(board_.board_state())
            << std::endl;
  std::swap(moving_player_, unmoving_player_);
}
void FiveInARowGame::RenderPieces(const ShaderProgram & shader_program) const {
  for (const auto & i : board_.history_moves()) {
    SetUniformsForAMove(shader_program, i);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }
}
void FiveInARowGame::SetUniformsForAMove(const ShaderProgram & shader_program,
                                         const ::Move & move) const {
  const auto & x = move.coordinate.x();
  const auto & y = move.coordinate.y();
  const auto & stone_type = move.stone_type;
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(x - 3, y - 3, 0.0f));
  const glm::mat4 transposed_and_inverse_model =
      glm::transpose(glm::inverse(model));
  shader_program.SetMatrix4("model", model);
  // TODO: change to this
  // shader_program.SetTransposedMatrix4("transposed_and_inverse_model",
  // glm::inverse(model));
  shader_program.SetMatrix4("transposed_and_inverse_model",
                            transposed_and_inverse_model);
  shader_program.BindTexture(stone_texture_by_stone_type(stone_type),
                             "material.diffuse_sampler", 0);
  shader_program.BindTexture(specular_map, "material.specular_sampler", 1);
}
