#pragma once

#define SPDLOG_FMT_EXTERNAL
#include <spdlog/async.h>
#include <spdlog/async_logger.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <memory>
#include <vector>

namespace sv {

enum class Severity {
  Info = 0,
  Error
};

enum class LogType {
  File = 0,
  FileAndStdout  // Default value
};

class Logger {
 public:
  static Logger& Instance(const std::filesystem::path& file = "default.log") {
    static Logger instance(file);
    return instance;
  }

  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

  void Write(Severity severity, const std::string& message, LogType type = LogType::FileAndStdout) {
    spdlog::level::level_enum lvl;
    switch (severity) {
      case Severity::Info:
        lvl = spdlog::level::info;
        break;
      case Severity::Error:
        lvl = spdlog::level::err;
        break;
      default:
        lvl = spdlog::level::debug;
        break;
    }

    fileLogger_->log(lvl, message);
    if (type == LogType::FileAndStdout) {
      stdoutLogger_->log(lvl, message);
    }
  }

 private:
  Logger(const std::filesystem::path& file) : file_(file) {
    spdlog::init_thread_pool(8192, 1);

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(file_.string(), true);
    fileLogger_ = std::make_shared<spdlog::async_logger>(
        "async_file_logger", file_sink, spdlog::thread_pool(),
        spdlog::async_overflow_policy::block);

    spdlog::register_logger(fileLogger_);

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    stdoutLogger_ = std::make_shared<spdlog::async_logger>(
        "async_console_logger", console_sink, spdlog::thread_pool(),
        spdlog::async_overflow_policy::block);

    spdlog::register_logger(stdoutLogger_);

    fileLogger_->set_pattern("%Y-%m-%d %H:%M:%S.%e [%l] %v");
    fileLogger_->flush_on(spdlog::level::info);

    stdoutLogger_->set_pattern("%Y-%m-%d %H:%M:%S.%e [%l] %v");
  }

  std::filesystem::path file_;
  std::shared_ptr<spdlog::logger> fileLogger_;
  std::shared_ptr<spdlog::logger> stdoutLogger_;
};

}  // namespace sv
