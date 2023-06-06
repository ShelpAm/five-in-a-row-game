#include "five_in_a_row_game/five_in_a_row_game.h"

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
      std::swap(moving_player_, unmoving_player_);
      break;
    case State::kStateStoped:
      break;
    case State::kStateEnded:
      break;
  }
}

void FiveInARowGame::Render(const ShaderProgram & shader_program) const {
  static auto SetUniforms = [this, &shader_program](const auto stone_type,
                                                    const auto i,
                                                    const auto j) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(i - 3, j - 3, 0.0f) - 1.0f);
    // TODO change to this
    // shader_program.SetTransposedMatrix4("transposed_and_inverse_model",
    // glm::inverse(model));
    shader_program.SetMatrix4("model", model);
    shader_program.SetMatrix4("transposed_and_inverse_model",
                              glm::transpose(glm::inverse(model)));
    shader_program.BindTexture(GetStoneTextureByStoneType(stone_type),
                               "material.diffuse_sampler", 0);
    shader_program.BindTexture(specular_map, "material.specular_sampler", 1);
  };
  static auto RenderStones = [this]() {
    for (std::size_t i = 0; i != board_.board_size(); i++) {
      for (std::size_t j = 0; j != board_.board_size(); j++) {
        if (const StoneType stone_type =
                board_.GetStoneTypeInCoordinate(BoardCoordinate(i, j));
            stone_type != StoneType::kStoneTypeEmpty) {
          SetUniforms(stone_type, i, j);
          glDrawArrays(GL_TRIANGLES, 0, 36);
        }
      }
    }
  };
  switch (state_) {
    case State::kStateNotStarted:
      break;
    case State::kStateStoped:
      // TODO: draw the `stopping` string.
      // SomeCodeDrawingStoppingString();
      RenderStones();
      break;
    case State::kStateStarted:
      RenderStones();
      break;
    case State::kStateEnded:
      RenderStones();
      break;
  }
  // printf("FiveInARowGame::Render invoked\n");
}

std::ostream & operator<<(std::ostream & os, const FiveInARowGame & game) {
  std::stringstream buf;
  buf << "FiveInARowGame {"
      << "\n  game_state_:" << state_string_map().at(game.state_)
      << "\n  num_moves_:" << game.board_.num_of_moves()
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

Texture2D & FiveInARowGame::GetStoneTextureByStoneType(
    const StoneType stone_type) {
  static Texture2D stone_textures[2]{Texture2D("black.png"),
                                     Texture2D{"white.png"}};
  static std::map<StoneType, Texture2D &> stone_type_to_texture_map_{
      {StoneType::kStoneTypeBlack, stone_textures[0]},
      {StoneType::kStoneTypeWhite, stone_textures[1]}};
  return stone_type_to_texture_map_.at(stone_type);
}

FiveInARowGame::FiveInARowGame(Player * black_player, Player * white_player) {
  black_player_ = moving_player_ = black_player;
  white_player_ = unmoving_player_ = white_player;
  moving_player_->set_stone_type(StoneType::kStoneTypeBlack);
  unmoving_player_->set_stone_type(StoneType::kStoneTypeWhite);
}
