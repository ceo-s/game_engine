#pragma once
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>


class Logger {
public:
  Logger();
  ~Logger();

private:
  static std::shared_ptr<spdlog::logger> coreLogger;
  static std::shared_ptr<spdlog::logger> clientLogger;


public:
  static void init();
  static  std::shared_ptr<spdlog::logger> &getCoreLogger() { return coreLogger; };
  static std::shared_ptr<spdlog::logger> &getClientLogger() { return clientLogger; };

};

#define CORE_DEBUG(...) Logger::getCoreLogger()->debug(__VA_ARGS__);
#define CORE_INFO(...) Logger::getCoreLogger()->info(__VA_ARGS__);
#define CORE_WARN(...) Logger::getCoreLogger()->warn(__VA_ARGS__);
#define CORE_TRACE(...) Logger::getCoreLogger()->trace(__VA_ARGS__);
#define CORE_ERROR(...) Logger::getCoreLogger()->error(__VA_ARGS__);

#define LOG_DEBUG(...) Logger::getClientLogger()->debug(__VA_ARGS__);
#define LOG_INFO(...) Logger::getClientLogger()->info(__VA_ARGS__);
#define LOG_WARN(...) Logger::getClientLogger()->warn(__VA_ARGS__);
#define LOG_TRACE(...) Logger::getClientLogger()->trace(__VA_ARGS__);
#define LOG_ERROR(...) Logger::getClientLogger()->error(__VA_ARGS__);
