//
// Created by small-sheep on 11/11/22.
//
#include "five_in_a_row_game/application.h"

#include <cctype>
#include <cmath>
#include <cstddef>
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

    std::ifstream vertex_file("shader/vertex.glsl");
    std::ifstream fragment_file("shader/fragment.glsl");
    std::stringstream vertex_buf, fragment_buf;
    vertex_buf << vertex_file.rdbuf();
    fragment_buf << fragment_file.rdbuf();
    shader_ = std::make_unique<Shader>(vertex_buf.str().c_str(),
                                       fragment_buf.str().c_str());
    glViewport(0, 0, 800, 600);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    // TODO: `xpos` and `ypos` won't work normally sometimes.
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    // glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    // glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
    if (glfwRawMouseMotionSupported()) {
      glfwSetInputMode(window_, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
  } catch (const GlfwWindowNotCreated &) {
    glfwTerminate();
    throw;
  } catch (const GladUninitialized &) {
    glfwTerminate();
    throw;
  }
}

Application::~Application() {}

void Application::Run() {
  float vertices[] = {
      //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // 右上
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // 右下
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // 左下
      -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // 左上
  };
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

  float texCoords[] = {
      0.0f, 0.0f,  // 左下角
      1.0f, 0.0f,  // 右下角
      0.5f, 1.0f   // 上中
  };
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  stbi_set_flip_vertically_on_load(true);
  int width, height, nrChannels;
  unsigned char * data =
      stbi_load("black.png", &width, &height, &nrChannels, 0);
  if (!data) {
    std::cout << "ERROR::STB::LOAD failed to load image\n";
    return;
  }
  unsigned tex0;
  glGenTextures(1, &tex0);
  glBindTexture(GL_TEXTURE_2D, tex0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);

  data = stbi_load("white.png", &width, &height, &nrChannels, 0);
  if (!data) {
    std::cout << "ERROR::STB::LOAD failed to load image\n";
    return;
  }
  unsigned tex1;
  glGenTextures(1, &tex1);
  glBindTexture(GL_TEXTURE_2D, tex1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);

  shader_->Uniform1i("tex0", 0);
  shader_->Uniform1i("tex1", 0);

  while (!glfwWindowShouldClose(window_)) {
    previous_frame_time_ = current_frame_time_;
    current_frame_time_ = glfwGetTime();
    auto delta_time = current_frame_time_ - previous_frame_time_;
    frame_per_second_ = static_cast<float>(CLOCKS_PER_SEC) / delta_time;
    // std::cout << frame_per_second_ << std::endl;

    ProcessInput();
    Update(delta_time);
    glBindVertexArray(vao);
    Render();

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f), (float)window_width_ / (float)window_height_, 0.1f,
        100.0f);
    shader_->UniformMatrix4fv("view", view);
    shader_->UniformMatrix4fv("projection", projection);
    shader_->Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex0);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window_);
    glfwPollEvents();
  }
}

void Application::ProcessInput() {
  ProcessCursor();
  ProcessKeyBoard();
}

void Application::ProcessCursor() {
  double xpos, ypos;
  glfwGetCursorPos(window_, &xpos, &ypos);
  // std::cout << "xpos:" << xpos << " ypos:" << ypos << "\n";

  static float prev_xpos = float(window_width_) / 2,
               prev_ypos = float(window_height_) / 2;
  float delta_x = xpos - prev_xpos, delta_y = -(ypos - prev_ypos);
  prev_xpos = xpos, prev_ypos = ypos;
  if (delta_x || delta_y) {
    std::cout << "Cursor position: " << xpos << ", " << ypos << " (" << delta_x
              << " " << delta_y << ")\n";
  }

  float sensitivity = 0.05f;
  yaw += delta_x * sensitivity;
  pitch += delta_y * sensitivity;
  if (pitch > 89.0f) pitch = 89.0f;
  if (pitch < -89.0f) pitch = -89.0f;
  glm::vec3 front;
  front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
  front.y = sin(glm::radians(pitch));
  front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
  cameraFront = glm::normalize(front);
}
void Application::ProcessKeyBoard() {
  if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window_, GLFW_TRUE);
  }
  auto delta_time = current_frame_time_ - previous_frame_time_;
  float cameraSpeed = 7.5f * delta_time;
  if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS)
    cameraPos += cameraSpeed * cameraFront;
  if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS)
    cameraPos -= cameraSpeed * cameraFront;
  if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS)
    cameraPos -=
        glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS)
    cameraPos +=
        glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

  if (glfwGetKey(window_, GLFW_KEY_G) == GLFW_PRESS) {
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
  }
  if (glfwGetKey(window_, GLFW_KEY_F) == GLFW_PRESS) {
    std::cout << "shader_program_:" << shader_->shader_program_ << "\n";
    if (game_) {
      std::cout << *game_;
    }
  }
}

void Application::Update(const std::size_t delta_tick) {
  if (game_) {
    game_->Update();
  }
}

void Application::Render() const {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // ClearScreen();

  if (game_) {
    game_->Render(*shader_);
  }
}
