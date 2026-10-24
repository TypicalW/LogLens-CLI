
#pragma once

#include "log_entry.hpp"

#include <cstddef>
#include <map>
#include <string>

struct LogAnalyzerResult {
    std::size_t totalEntries = 0;
    std::size_t malformedLines = 0;

    std::map<LogLevel, std::size_t> levelCounts;
    std::map<std::string, std::size_t> errorFrequencies;
};
