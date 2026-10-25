#pragma once

#include "log_entry.hpp"
#include "log_filter_options.hpp"

#include <vector>

class LogFilter {
public:
    std::vector<LogEntry> filter(
        const std::vector<LogEntry>& entries,
        const LogFilterOptions& options
    ) const;
};