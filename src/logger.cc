#include "five_in_a_row_game/logger.h"

#include <cassert>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

Logger & Logger::instance() {
  static Logger the_instance("log/");
  return the_instance;
}
Logger::Logger(const char * directory) : directory_(directory) {
  std::filesystem::create_directory(directory_);
  fs_.open(directory_ + "latest.log", std::ios::app | std::ios::binary);
  assert(fs_.is_open());
}
Logger::~Logger() { fs_.close(); }
void Logger::Log(const LogLevel & log_level, const char * content) {
  const std::string log_message = GenerateLogMessage(log_level, content);
  messages_to_print_.push_back(log_message);
  if (eager_mode_is_enabled_) {
    PrintMessages();
  }
}
void Logger::Log(const LogLevel & log_level, const std::string_view & content) {
  Log(log_level, content.data());
}
void Logger::EnableTerminal() { terminal_is_enabled_ = true; }
void Logger::DisableTerminal() { terminal_is_enabled_ = false; }
void Logger::Debug(const char * content) {
  Log(LogLevelType::LogLevelTypeDebug, content);
}

void Logger::Debug(const std::string_view & content) { Debug(content.data()); }
void Logger::Info(const char * content) {
  Log(LogLevelType::LogLevelTypeInfo, content);
}
void Logger::Info(const std::string_view & content) { Info(content.data()); }
void Logger::Warning(const char * content) {
  Log(LogLevelType::LogLevelTypeWarning, content);
}

void Logger::Warning(const std::string_view & content) {
  Warning(content.data());
}
void Logger::Error(const char * content) {
  Log(LogLevelType::LogLevelTypeError, content);
}

void Logger::Error(const std::string_view & content) { Error(content.data()); }
void Logger::Fatal(const char * content) {
  Log(LogLevelType::LogLevelTypeFatal, content);
}

void Logger::Fatal(const std::string_view & content) { Fatal(content.data()); }
const std::string Logger::GenerateLogMessage(const LogLevel & log_level,
                                             const char * content) const {
  std::stringstream ss;
  ss << "[" << time_string_ << "] [" << log_level << "] " << content << "\n";
  return ss.str();
}
void Logger::PrintMessages() {
  assert(fs_.good());
  // TODO: Check if this is right. (&&)
  for (const auto & message : messages_to_print_) {
    if (file_is_enabled_) {
      fs_ << message;
    }
    if (terminal_is_enabled_) {
      std::cout << message;
    }
    history_messages_.push_back(message);
  }
  messages_to_print_.clear();
}
