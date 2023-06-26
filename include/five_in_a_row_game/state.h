#ifndef FIVE_IN_A_ROW_GAME_STATE_H_
#define FIVE_IN_A_ROW_GAME_STATE_H_

#include <cstddef>
#include <map>
#include <string>

enum class StateType : std::size_t {
  kStateNotStarted,
  kStateStarted,
  kStateStoped,
  kStateEnded
};

class State {
 public:
  State(const StateType state) : state_(state) {}

  operator StateType() const { return state_; }

  operator std::string() const {
    static std::map<StateType, std::string> state_string_map{
        {StateType::kStateNotStarted, "kStateNotStarted"},
        {StateType::kStateStarted, "kStateStarted"},
        {StateType::kStateStoped, "kStateStoped"},
        {StateType::kStateEnded, "kStateEnded"}};
    return state_string_map.at(state_);
  }

 private:
  StateType state_;
};

#endif  // FIVE_IN_A_ROW_GAME_STATE_H_
