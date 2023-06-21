#ifndef FIVE_IN_A_ROW_GAME_LOGGER_H
#define FIVE_IN_A_ROW_GAME_LOGGER_H

#include <cassert>
#include <fstream>
#include <string>
#include <string_view>

// TODO: add asynchronous logging
class Logger {
 public:
  static Logger & instance();
  Logger(const char * directory);
  ~Logger();
  void Log(const char * content);
  void Log(const std::string_view & content);

 private:
  std::string directory_ = "log/";
  std::string time_string_ = "unimplemented";
  std::fstream fs_;
};

#endif  // FIVE_IN_A_ROW_GAME_LOGGER_H
