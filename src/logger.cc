#include "five_in_a_row_game/logger.h"

#include <cassert>
#include <filesystem>

Logger & Logger::instance() {
  static Logger the_instance("log/");
  return the_instance;
}
Logger::Logger(const char * directory) : directory_(directory) {
  std::filesystem::create_directory(directory_);
  fs_.open(directory_ + "latest.log", std::ios::app | std::ios::binary);
  if (!fs_.is_open()) {
    assert(false);
  }
}
Logger::~Logger() { fs_.close(); }
void Logger::Log(const char * content) {
  if (!fs_) {
    assert(false);
  }
  fs_ << "[" << time_string_ << "] [DEBUG] " << content << "\n";
}
void Logger::Log(const std::string_view & content) {
  if (!fs_) {
    assert(false);
  }
  fs_ << "[" << time_string_ << "] [DEBUG] " << content << "\n";
}
