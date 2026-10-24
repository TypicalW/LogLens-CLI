#pragma once

#include <string>
#include <utility>

enum class LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class LogEntry {
public:
    LogEntry(std::string timestamp, LogLevel level, std::string message)
        : timestamp_(std::move(timestamp)),
          level_(level),
          message_(std::move(message)) {}

    const std::string& getTimestamp() const {
        return timestamp_;
    }

    LogLevel getLevel() const {
        return level_;
    }

    const std::string& getMessage() const {
        return message_;
    }

private:
    std::string timestamp_;
    LogLevel level_;
    std::string message_;
};
