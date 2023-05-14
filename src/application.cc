//
// Created by small-sheep on 11/11/22.
//
#include "five_in_a_row_game/application.h"

#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>

#include "GLFW/glfw3.h"
#include "five_in_a_row_game/easy_ai_player.h"
#include "five_in_a_row_game/easy_ai_player_factory.h"
#include "five_in_a_row_game/human_player_factory.h"
#include "five_in_a_row_game/main.h"
#include "five_in_a_row_game/player.h"
#include "five_in_a_row_game/shader.h"
#include "five_in_a_row_game/state.h"
#include "five_in_a_row_game/texture.h"
#include "glad/glad.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_projection.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "stb/stb_image.h"

void Application::Initialize() {
  if (!glfwInit()) {
    throw GlfwUninitialized();
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void Application::Terminate() { glfwTerminate(); }

Application::Application(const std::size_t window_width,
                         const std::size_t window_height,
                         const char * window_title)
    : window_width_(window_width), window_height_(window_height) {
  try {
    window_ =
        glfwCreateWindow(window_width, window_height, window_title, NULL, NULL);
    if (!window_) {
      throw GlfwWindowNotCreated();
    }
    glfwMakeContextCurrent(window_);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      throw GladUninitialized();
    }
    glfwSetCursorPosCallback(window_, &cursor_pos_callback);
    glfwSetKeyCallback(window_, &key_callback);
    glfwSetScrollCallback(window_, &scroll_callback);
    // `xpos` and `ypos` doesn't work properly with `GLFW_CURSOR_DISABLED` (only
    // in VMWARE). So here we use `GLFW_CURSOR_NORMAL` to avoid that problem.
    // glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    if (glfwRawMouseMotionSupported()) {
      glfwSetInputMode(window_, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
    AttachThis();

    std::ifstream vertex_file("shader/vertex.glsl");
    std::ifstream fragment_file("shader/fragment.glsl");
    std::stringstream vertex_buf, fragment_buf;
    vertex_buf << vertex_file.rdbuf();
    fragment_buf << fragment_file.rdbuf();
    shader_ = std::make_unique<Shader>(vertex_buf.str().c_str(),
                                       fragment_buf.str().c_str());
    glViewport(0, 0, 800, 600);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

  } catch (const GlfwWindowNotCreated &) {
    glfwTerminate();
    throw;
  } catch (const GladUninitialized &) {
    glfwTerminate();
    throw;
  }
}

Application::~Application() { DetachThis(); }

void Application::AttachThis() { window_application_map_[window_] = this; }

void Application::DetachThis() const {
  if (!window_application_map_.contains(window_)) {
    return;
  }
  window_application_map_.erase(window_application_map_.find(window_));
}

void Application::CursorPosCallback(double xpos, double ypos) {
  static float prev_xpos = float(window_width_) / 2,
               prev_ypos = float(window_height_) / 2;
  float delta_x = xpos - prev_xpos, delta_y = -(ypos - prev_ypos);
  prev_xpos = xpos, prev_ypos = ypos;
  if (delta_x || delta_y) {
    std::cout << "Cursor position: " << xpos << ", " << ypos << " (" << delta_x
              << " " << delta_y << ")\n";
  }

  float sensitivity = 0.05f;
  camera_.add_yaw(delta_x * sensitivity);
  camera_.add_pitch(delta_y * sensitivity);
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
        glfwSetWindowShouldClose(window_, GLFW_TRUE);
        break;
      case GLFW_KEY_UNKNOWN:
      default:
        break;
    }
  }
  if (action == GLFW_RELEASE) {
    switch (key) {
      case GLFW_KEY_UNKNOWN:
      default:
        break;
    }
  }
}

void Application::ScrollCallback(double xoffset, double yoffset) {
  std::cout << "Scrolling: " << xoffset << ", " << yoffset << "\n";
  yoffset *= 3;
  camera_.add_fov(-yoffset);
}

void Application::Run() {
  float vertices[] = {
      // positions          // normals           // texture coords
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.5f,  -0.5f,
      -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 0.0f,
      0.0f,  -1.0f, 1.0f,  1.0f,  0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,
      1.0f,  1.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,

      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.5f,  -0.5f,
      0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,
      0.0f,  1.0f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      1.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

      -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,
      -0.5f, -1.0f, 0.0f,  0.0f,  1.0f,  1.0f,  -0.5f, -0.5f, -0.5f, -1.0f,
      0.0f,  0.0f,  0.0f,  1.0f,  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
      0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  0.0f,  0.0f,
      -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.0f,

      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,
      -0.5f, 1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 1.0f,
      0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
      0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.5f,  -0.5f,
      -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  0.0f,
      -1.0f, 0.0f,  1.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,
      1.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f,  1.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.5f,  0.5f,
      -0.5f, 0.0f,  1.0f,  0.0f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,
      1.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f};
  unsigned int indices[] = {
      0, 1, 2,  // first Triangle
      0, 2, 3,
  };
  unsigned vbo, ebo, vao;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glBindVertexArray(0);

  shader_->Uniform1i("material.diffuse_map", 0);
  shader_->Uniform1i("material.specular_map", 1);
  shader_->Uniform1f("material.shininess", 32.0f);

  while (!glfwWindowShouldClose(window_)) {
    previous_frame_time_ = current_frame_time_;
    current_frame_time_ = glfwGetTime();
    auto delta_time = current_frame_time_ - previous_frame_time_;
    frame_per_second_ = 1.0f / delta_time;
    // std::cout << "Fps:" << frame_per_second_ << "\n";
    // std::cout << "Curr time, prev time: " << current_frame_time_ << " "
    //           << previous_frame_time_ << " (" << delta_time << ")\n";
    // std::cout << "Delta time: " << delta_time << "\n";

    Update(delta_time);
    shader_->Uniform3f("directional_light.direction", 0.1, -0.4, -1);
    shader_->Uniform3f("directional_light.ambient", 0.1f, 0.1f, 0.1f);
    shader_->Uniform3f("directional_light.diffuse", 0.7f, 0.7f, 0.7f);
    shader_->Uniform3f("directional_light.specular", 0.1f, 0.1f, 0.1f);
    shader_->Uniform1f("light.constant", 1.0f);
    shader_->Uniform1f("light.linear", 0.09f);
    shader_->Uniform1f("light.quadratic", 0.032f);
    shader_->Use();
    glBindVertexArray(vao);
    Render();

    glfwSwapBuffers(window_);
    glfwPollEvents();
  }
}

void Application::Update(const float delta_time) {
  if (game_) {
    game_->Update();
  }
  camera_.Update(delta_time, keys_);
  shader_->UniformMatrix4fv("view", camera_.look_at());
  glm::mat4 projection = glm::perspective(
      glm::radians(camera_.fov()), (float)window_width_ / (float)window_height_,
      0.1f, 100.0f);
  shader_->UniformMatrix4fv("projection", projection);
  shader_->Uniform3f("world_light_pos", 0, 4, 5);
}

void Application::Render() const {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // ClearScreen();

  if (game_) {
    game_->Render(*shader_);
  }
}

std::map<const GLFWwindow *, Application *>
    Application::window_application_map_{};
