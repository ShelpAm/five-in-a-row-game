#ifndef FIVE_IN_A_ROW_GAME_STONE_TYPE_H_
#define FIVE_IN_A_ROW_GAME_STONE_TYPE_H_

#include <map>
#include <string>

enum class StoneType : int {
  kStoneTypeEmpty,
  kStoneTypeBlack,
  kStoneTypeWhite
};

// enum class StoneColor : unsigned { kStoneColorBlack, kStoneColorWhite };

inline const auto & stone_type_string_map() {
  static std::map<StoneType, std::string> stone_type_string_map{
      {StoneType::kStoneTypeEmpty, "kStoneTypeEmpty"},
      {StoneType::kStoneTypeBlack, "kStoneTypeBlack"},
      {StoneType::kStoneTypeWhite, "kStoneTypeWhite"}};
  return stone_type_string_map;
}

inline const auto & stone_code_map() {
  static std::map<StoneType, char> stone_code_map{
      {StoneType::kStoneTypeEmpty, ' '},
      {StoneType::kStoneTypeBlack, '1'},
      {StoneType::kStoneTypeWhite, '2'}};
  return stone_code_map;
}

#endif  // FIVE_IN_A_ROW_GAME_STONE_TYPE_H_
