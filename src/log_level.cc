#include "five_in_a_row_game/log_level.h"

#include <map>

LogLevel::operator const char *() const {
  static const std::map<LogLevelType, const char *> log_level_map_{
      {LogLevelType::LogLevelTypeDebug, "DEBUG"},
      {LogLevelType::LogLevelTypeInfo, "INFO"},
      {LogLevelType::LogLevelTypeWarning, "WARNING"},
      {LogLevelType::LogLevelTypeError, "ERROR"},
      {LogLevelType::LogLevelTypeFatal, "FATAL"}};
  return log_level_map_.at(this->log_level_);
}
LogLevel::LogLevel(const LogLevelType & log_level) : log_level_(log_level) {}
