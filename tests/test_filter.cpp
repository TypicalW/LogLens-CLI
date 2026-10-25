#include "log_filter.hpp"

#include <optional>
#include <string>
#include <vector>

int main() {
    const std::vector<LogEntry> entries = {
        {"2026-10-24 10:00:00", LogLevel::INFO, "Server started"},
        {"2026-10-24 10:01:00", LogLevel::ERROR, "Database timeout"},
        {"2026-10-24 10:02:00", LogLevel::WARN, "Memory usage high"},
        {"2026-10-24 10:03:00", LogLevel::ERROR, "Connection refused"},
        {"2026-10-24 10:04:00", LogLevel::ERROR, "Database timeout"},
        {"2026-10-24 10:05:00", LogLevel::DEBUG, "Cache miss"}
    };

    LogFilter filter;

    // Test 1: No filters should return every entry.
    LogFilterOptions allOptions;
    const auto all = filter.filter(entries, allOptions);

    if (all.size() != 6) return 1;

    // Test 2: Severity filter.
    LogFilterOptions errorOptions;
    errorOptions.level = LogLevel::ERROR;

    const auto errors = filter.filter(entries, errorOptions);

    if (errors.size() != 3) return 2;

    for (const LogEntry& entry : errors) {
        if (entry.getLevel() != LogLevel::ERROR) return 3;
    }

    // Test 3: Case-insensitive keyword filter.
    LogFilterOptions keywordOptions;
    keywordOptions.keyword = "dAtAbAsE";

    const auto databaseEntries = filter.filter(entries, keywordOptions);

    if (databaseEntries.size() != 2) return 4;

    for (const LogEntry& entry : databaseEntries) {
        if (entry.getMessage().find("Database") == std::string::npos) {
            return 5;
        }
    }

    // Test 4: Combined severity AND keyword.
    LogFilterOptions combinedOptions;
    combinedOptions.level = LogLevel::ERROR;
    combinedOptions.keyword = "database";

    const auto databaseErrors = filter.filter(entries, combinedOptions);

    if (databaseErrors.size() != 2) return 6;

    for (const LogEntry& entry : databaseErrors) {
        if (entry.getLevel() != LogLevel::ERROR) return 7;
    }

    // Test 5: A keyword with no matches.
    LogFilterOptions noMatchOptions;
    noMatchOptions.keyword = "nonexistent";

    const auto noMatches = filter.filter(entries, noMatchOptions);

    if (!noMatches.empty()) return 8;

    // Test 6: The original input must remain unchanged.
    if (entries.size() != 6) return 9;

    // Test 7: Matching entries must preserve their original order.
    if (errors[0].getMessage() != "Database timeout") return 10;
    if (errors[1].getMessage() != "Connection refused") return 11;
    if (errors[2].getMessage() != "Database timeout") return 12;

    return 0;
}