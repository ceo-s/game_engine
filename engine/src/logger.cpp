#include "pch/pch.h"
#include "logger.h"


std::shared_ptr<spdlog::logger> Logger::coreLogger;
std::shared_ptr<spdlog::logger> Logger::clientLogger;

Logger::Logger() {

}

Logger::~Logger() {

}void Logger::init() {
  spdlog::set_pattern("%^[%n %l] %v |%$ %T");
  coreLogger = spdlog::stdout_color_mt("CORE");
  coreLogger->set_level(spdlog::level::trace);
  clientLogger = spdlog::stdout_color_mt("CLIENT");
  clientLogger->set_level(spdlog::level::trace);

}
