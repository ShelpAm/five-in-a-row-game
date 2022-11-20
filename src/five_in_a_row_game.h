//
// Created by small-sheep on 11/10/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_FIVE_IN_A_ROW_GAME_H
#define FIVE_IN_A_ROW_GAME_SRC_FIVE_IN_A_ROW_GAME_H

#include <memory>
#include <string>
#include "player.h"

class FiveInARowGame {
 public:
  explicit FiveInARowGame();

  void Start(Player *first_hand_player_ptr, Player *second_hand_player_ptr);

  void Tick();

  void ProcessInput();

  // @brief: Update processes data
  void Update();

  void Render() const;

  void ParseCommand(const std::string &command);

 public:
  bool GameIsOn() const;

  void SetGameIsOn(bool game_is_on);

  int FramePerSecond() const;

  void SetFramePerSecond(int frame_per_second);

 private:
  bool game_is_on_ = false;
  int frame_per_second_ = 0;
  int last_frame_time_ = 0, current_frame_time_ = 0;
  std::unique_ptr<Board> board_pointer_;
  Player *first_hand_player_ptr_, *second_hand_player_ptr_;
};

#endif //FIVE_IN_A_ROW_GAME_SRC_FIVE_IN_A_ROW_GAME_H
