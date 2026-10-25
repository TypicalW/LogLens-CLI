#pragma once

#include "log_entry.hpp"

#include <optional>
#include <string>

struct LogFilterOptions {
    std::optional<LogLevel> level;
    std::string keyword;
};