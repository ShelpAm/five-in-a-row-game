#ifndef FIVE_IN_A_ROW_GAME_STATE_H_
#define FIVE_IN_A_ROW_GAME_STATE_H_

#include <cstddef>
#include <map>
#include <string>

enum class State : std::size_t {
  kStateNotStarted,
  kStateStarted,
  kStateStoped,
  kStateEnded
};

inline const auto & state_string_map() {
  static std::map<State, std::string> state_string_map{
      {State::kStateNotStarted, "kStateNotStarted"},
      {State::kStateStarted, "kStateStarted"},
      {State::kStateStoped, "kStateStoped"},
      {State::kStateEnded, "kStateEnded"}};
  return state_string_map;
}

#endif  // FIVE_IN_A_ROW_GAME_STATE_H_
