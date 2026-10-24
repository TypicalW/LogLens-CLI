
#pragma once

#include "log_entry.hpp"

#include <cstddef>
#include <vector>

struct LogReadResult {
    std::vector<LogEntry> entries;
    std::size_t malformedLines = 0;
};
