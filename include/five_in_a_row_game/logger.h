#ifndef FIVE_IN_A_ROW_GAME_LOGGER_H
#define FIVE_IN_A_ROW_GAME_LOGGER_H

#include <cassert>
#include <fstream>
#include <list>
#include <map>
#include <string>
#include <string_view>

#include "five_in_a_row_game/log_level.h"

// TODO: add asynchronous logging. For example, using multi-thread is a good
// practice.
// TODO: use multi-parameter logging instead of single parameter logging like
// `content`
class Logger {
 public:
  static Logger & instance();
  Logger(const char * directory);
  ~Logger();

  void Log(const LogLevel & log_level, const char * content);
  void Log(const LogLevel & log_level, const std::string_view & content);

  void Debug(const char * content);
  void Debug(const std::string_view & content);

  void Info(const char * content);
  void Info(const std::string_view & content);

  void Warning(const char * content);
  void Warning(const std::string_view & content);

  void Error(const char * content);
  void Error(const std::string_view & content);

  void Fatal(const char * content);
  void Fatal(const std::string_view & content);

  void EnableTerminal();
  void DisableTerminal();

  void EnableFile();
  void DisableFile();

 private:
  const std::string GenerateLogMessage(const LogLevel & log_level,
                                       const char * content) const;

  void PrintMessages();

  std::string directory_ = "log/";
  std::string time_string_ = "unimplemented";
  std::fstream fs_;
  std::list<std::string> history_messages_;
  std::list<std::string> messages_to_print_;
  LogLevel minimum_level_ = LogLevelType::LogLevelTypeInfo;
  bool file_is_enabled_ = true;
  bool terminal_is_enabled_ = false;
  // TODO: implement this
  bool eager_mode_is_enabled_ = true;
};

#endif  // FIVE_IN_A_ROW_GAME_LOGGER_H
