//
// Created by small-sheep on 11/11/22.
//
#include "five_in_a_row_game/application.h"

#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>

#include "GLFW/glfw3.h"
#include "five_in_a_row_game/callbacks.h"
#include "five_in_a_row_game/easy_ai_player.h"
#include "five_in_a_row_game/easy_ai_player_factory.h"
#include "five_in_a_row_game/fragment_shader.h"
#include "five_in_a_row_game/human_player_factory.h"
#include "five_in_a_row_game/main.h"
#include "five_in_a_row_game/player.h"
#include "five_in_a_row_game/shader_program.h"
#include "five_in_a_row_game/state.h"
#include "five_in_a_row_game/texture.h"
#include "five_in_a_row_game/vertex_shader.h"
#include "five_in_a_row_game/window.h"
#include "glad/glad.h"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_projection.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/trigonometric.hpp"
#include "stb/stb_image.h"

void Application::Initialize() {
  glfwSetErrorCallback(&error_callback);
  if (!glfwInit()) {
    throw GlfwUninitialized();
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef DEBUG
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif  // DEBUG
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void Application::Terminate() { glfwTerminate(); }

Application::Application() : Application("untitled window", 800, 600) {}

Application::Application(const char * window_title, const int window_width,
                         const int window_height)
    : window_(this, window_title, window_width, window_height),
      shader_(VertexShader(0, "shader/vertex.vert"),
              FragmentShader(0, "shader/fragment.frag")),
      simple_shader_(VertexShader(0, "shader/simple.vert"),
                     FragmentShader(0, "shader/simple.frag")) {
  window_.set_depth_test_enabled(true);
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

Application::~Application() {}

void Application::CursorPosCallback(double x_pos, double y_pos) {
  static float prev_x_pos = float(window_.width()) / 2,
               prev_y_pos = float(window_.height()) / 2;
  float delta_x = x_pos - prev_x_pos, delta_y = -(y_pos - prev_y_pos);
  prev_x_pos = x_pos;
  prev_y_pos = y_pos;
  if (delta_x || delta_y) {
    // std::cout << "Cursor position: " << x_pos << ", " << y_pos << " ("
    // << delta_x << " " << delta_y << ")\n";
  }

  float sensitivity = 0.05f;
  camera_.add_yaw(delta_x * sensitivity);
  camera_.add_pitch(delta_y * sensitivity);
  camera_.set_direction_changed(true);
}

void Application::KeyCallback(int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    std::cout << "Key: " << char(key) << " pressed\n";
    keys_[key] = true;
  } else if (action == GLFW_RELEASE) {
    std::cout << "Key: " << char(key) << " released\n";
    keys_[key] = false;
  }
  if (action == GLFW_PRESS) {
    switch (key) {
      case GLFW_KEY_F:
        if (game_) {
          std::cout << *game_;
        }
        break;
      case GLFW_KEY_G: {
        auto human_player = HumanPlayerFactory::Instance().MakePlayer();
        auto ai_player1 = EasyAIPlayerFactory::Instance().MakePlayer();
        auto ai_player2 = EasyAIPlayerFactory::Instance().MakePlayer();
        players_.push_back(human_player);
        players_.push_back(ai_player1);
        players_.push_back(ai_player2);
        human_player->set_name("test_user1");
        ai_player1->set_name("easy_ai_player1");
        ai_player2->set_name("easy_ai_player2");

        history_games_.push_back(game_);
        game_ = new FiveInARowGame(ai_player1.get(), ai_player2.get());
        game_->Start();
        break;
      }
      case GLFW_KEY_ESCAPE:
        window_.set_should_close(true);
        break;
      case GLFW_KEY_UNKNOWN:
      default:
        break;
    }
  } else if (action == GLFW_RELEASE) {
    switch (key) {
      case GLFW_KEY_UNKNOWN:
      default:
        break;
    }
  }
}

void Application::ScrollCallback(double x_offset, double y_offset) {
  std::cout << "Scrolling: " << x_offset << ", " << y_offset << "\n";
  y_offset *= 3;
  camera_.add_fov(-y_offset);
}

void Application::Run() {
  constexpr float vertices[]{
      // positions          // normals           // texture coords
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.5f,  -0.5f,
      -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 0.0f,
      0.0f,  -1.0f, 1.0f,  1.0f,  0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,
      1.0f,  1.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f,
      0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,
      0.0f,  1.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
      -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  -0.5f, -0.5f,
      0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  -1.0f,
      0.0f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f,
      1.0f,  1.0f,  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
      -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f,  1.0f,  -0.5f, -0.5f,
      0.5f,  -1.0f, 0.0f,  0.0f,  0.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  -1.0f,
      0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      1.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
      0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f,
      -0.5f, 1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  1.0f,
      0.0f,  0.0f,  0.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      1.0f,  0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f,  1.0f,
      0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f,  1.0f,  0.5f,  -0.5f,
      0.5f,  0.0f,  -1.0f, 0.0f,  1.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,
      -1.0f, 0.0f,  1.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,
      0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f,  1.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.5f,  0.5f,
      -0.5f, 0.0f,  1.0f,  0.0f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,
      1.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f};
  constexpr unsigned int indices[] = {
      0, 1, 2, 0, 2, 3,
  };
  unsigned vao;
  unsigned vbo;
  unsigned ebo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  constexpr glm::vec3 ambient(0.4f);
  constexpr glm::vec3 diffuse(0.4f);
  constexpr glm::vec3 specular(0.2f);
  constexpr glm::vec3 kLightDirection(0.0f, -0.3f, -1.0f);
  constexpr float kConstantAttenuation = 1.0f;
  constexpr float kLinearAttenuation = 0.09f;
  constexpr float kQuadraticAttenuation = 0.032f;
  const float kSpotlightCosPhi = glm::cos(glm::radians(12.5f));
  const float kSpotlightCosGamma = glm::cos(glm::radians(17.5f));
  shader_.SetVector3("dir_light.light.ambient", ambient);
  shader_.SetVector3("dir_light.light.diffuse", diffuse);
  shader_.SetVector3("dir_light.light.specular", specular);
  shader_.SetVector3("dir_light.direction", kLightDirection);
  shader_.SetVector3("point_lights[0].light.ambient", ambient);
  shader_.SetVector3("point_lights[0].light.diffuse", diffuse);
  shader_.SetVector3("point_lights[0].light.specular", specular);
  shader_.SetVector3("point_lights[0].position", glm::vec3(0, 0, -3));
  shader_.SetFloat("point_lights[0].attenuation.constant",
                   kConstantAttenuation);
  shader_.SetFloat("point_lights[0].attenuation.linear", kLinearAttenuation);
  shader_.SetFloat("point_lights[0].attenuation.quadratic",
                   kQuadraticAttenuation);
  shader_.SetVector3("spot_light.light.ambient", ambient);
  shader_.SetVector3("spot_light.light.diffuse", diffuse);
  shader_.SetVector3("spot_light.light.specular", specular);
  shader_.SetFloat("spot_light.attenuation.constant", kConstantAttenuation);
  shader_.SetFloat("spot_light.attenuation.linear", kLinearAttenuation);
  shader_.SetFloat("spot_light.attenuation.quadratic", kQuadraticAttenuation);
  shader_.SetFloat("spot_light.cos_phi", kSpotlightCosPhi);
  shader_.SetFloat("spot_light.cos_gamma", kSpotlightCosGamma);
  shader_.SetFloat("material.shininess", 64.0f);

  Texture2D tex("awesome_face.png");

  while (!window_.should_close()) {
    previous_frame_time_ = current_frame_time_;
    current_frame_time_ = glfwGetTime();
    auto delta_time = current_frame_time_ - previous_frame_time_;
    frame_per_second_ = 1.0f / delta_time;
    // std::cout << "Fps:" << frame_per_second_ << "\n";
    // std::cout << "Curr time, prev time: " << current_frame_time_ << " "
    //           << previous_frame_time_ << " (" << delta_time << ")\n";
    // std::cout << "Delta time: " << delta_time << "\n";

    Update(delta_time);

    window_.Clear();
    glBindVertexArray(vao);
    shader_.Use();
    Render();
    tex.Render(simple_shader_, window_, glm::vec3(0, 0, 0),
               glm::vec3(0.8, 0.3, 1), glm::vec3(1.0f));

    window_.SwapBuffers();
    Window::PollEvents();
  }
}

void Application::Update(const float delta_time) {
  if (game_) {
    game_->Update();
  }
  camera_.Update(delta_time, keys_);
  camera_.SetUniforms(shader_, window_);
  // Because every object has different position, we need to send the model to
  // the shader later.
  // shader_.SetMatrix4("model", glm::mat4(1.0f));
}

void Application::Render() const {
  if (game_) {
    game_->Render(shader_);
  }
}
