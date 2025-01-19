#pragma once

#include <atomic>
#include <condition_variable>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

namespace sv {

enum LogCategory { INFO = 0, WARN = 1, ERROR = 2 };

class Logger {
 public:
  Logger(const std::filesystem::path& filename) : stopLogging_(false) {
    logThread_ = std::thread(&Logger::ProcessLogs, this, filename);
  }

  ~Logger() { Stop(); }

  void Log(LogCategory category, const std::string& message) {
    {
      std::lock_guard<std::mutex> lock(queueMutex_);
      logQueue_.push(std::move(
          std::string{"[" + LogCategoryToString(category) + "]\t\t" + message}));
    }
    queueCondition_.notify_one();
  }

  void Stop() {
    {
      std::lock_guard<std::mutex> lock(queueMutex_);
      stopLogging_ = true;
    }
    queueCondition_.notify_one();
    if (logThread_.joinable()) {
      logThread_.join();
    }
  }

 private:
  std::queue<std::string> logQueue_;
  std::mutex queueMutex_;
  std::condition_variable queueCondition_;
  std::thread logThread_;
  std::atomic<bool> stopLogging_;

  void ProcessLogs(const std::string& filename) {
    std::ofstream logFile(filename, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
      std::cerr << "Failed to open log file: " << filename << std::endl;
      return;
    }

    while (true) {
      std::unique_lock<std::mutex> lock(queueMutex_);
      queueCondition_.wait(
          lock, [this] { return !logQueue_.empty() || stopLogging_; });

      while (!logQueue_.empty()) {
        logFile << logQueue_.front() << std::endl;
        logQueue_.pop();
      }

      if (stopLogging_) {
        break;
      }
    }

    logFile.close();
  }

  std::string LogCategoryToString(LogCategory category) {
    switch (category) {
      case LogCategory::INFO:
        return "INFO";
      case LogCategory::WARN:
        return "WARN";
      case LogCategory::ERROR:
        return "ERROR";
    }

    return "LOG";
  }
};

}  // namespace sv
