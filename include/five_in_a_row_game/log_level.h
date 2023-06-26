#ifndef FIVE_IN_A_ROW_GAME_LOG_LEVEL_H
#define FIVE_IN_A_ROW_GAME_LOG_LEVEL_H

#include <string>

enum class LogLevelType : int {
  LogLevelTypeDebug,
  LogLevelTypeInfo,
  LogLevelTypeWarning,
  LogLevelTypeError,
  LogLevelTypeFatal,
};

class LogLevel {
 public:
  LogLevel() = default;
  LogLevel(const LogLevelType & level);
  LogLevel(LogLevel &&) = default;
  LogLevel(const LogLevel &) = default;
  LogLevel & operator=(LogLevel &&) = default;
  LogLevel & operator=(const LogLevel &) = default;
  ~LogLevel() = default;

  operator const char *() const;

 private:
  LogLevelType log_level_;
};

#endif  // FIVE_IN_A_ROW_GAME_LOG_LEVEL_H
