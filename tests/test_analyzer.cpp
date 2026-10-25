
#include "log_analyzer.hpp"

#include <string>
#include <utility>
#include <vector>

int main() {
    LogAnalyzer analyzer;

    // Prepare input as if it came from LogReader.
    LogReadResult input;

    input.entries.emplace_back(
        "2026-10-24 10:00:00",
        LogLevel::INFO,
        "Server started"
    );

    input.entries.emplace_back(
        "2026-10-24 10:01:00",
        LogLevel::ERROR,
        "Database timeout"
    );

    input.entries.emplace_back(
        "2026-10-24 10:02:00",
        LogLevel::ERROR,
        "Connection refused"
    );

    input.entries.emplace_back(
        "2026-10-24 10:03:00",
        LogLevel::WARN,
        "Memory usage high"
    );

    input.entries.emplace_back(
        "2026-10-24 10:04:00",
        LogLevel::ERROR,
        "Database timeout"
    );

    input.entries.emplace_back(
        "2026-10-24 10:05:00",
        LogLevel::DEBUG,
        "Cache miss"
    );

    input.entries.emplace_back(
        "2026-10-24 10:06:00",
        LogLevel::ERROR,
        "Connection refused"
    );

    input.malformedLines = 2;

    // Test analysis summary.
    const LogAnalyzerResult result = analyzer.analyze(input);

    if (result.totalEntries != 7) {
        return 1;
    }

    if (result.malformedLines != 2) {
        return 2;
    }

    if (result.levelCounts.at(LogLevel::DEBUG) != 1) {
        return 3;
    }

    if (result.levelCounts.at(LogLevel::INFO) != 1) {
        return 4;
    }

    if (result.levelCounts.at(LogLevel::WARN) != 1) {
        return 5;
    }

    if (result.levelCounts.at(LogLevel::ERROR) != 4) {
        return 6;
    }

    // Test error-message frequencies.
    if (result.errorFrequencies.at("Database timeout") != 2) {
        return 7;
    }

    if (result.errorFrequencies.at("Connection refused") != 2) {
        return 8;
    }

    if (result.errorFrequencies.size() != 2) {
        return 9;
    }

    // Test top-N ranking and alphabetical tie-breaking.
    const auto topErrors = analyzer.getTopErrors(result, 2);

    if (topErrors.size() != 2) {
        return 10;
    }

    if (topErrors[0].first != "Connection refused" ||
        topErrors[0].second != 2) {
        return 11;
    }

    if (topErrors[1].first != "Database timeout" ||
        topErrors[1].second != 2) {
        return 12;
    }

    // Requesting more errors than exist should return all errors.
    const auto allErrors = analyzer.getTopErrors(result, 10);

    if (allErrors.size() != 2) {
        return 13;
    }

    // Requesting zero errors should return an empty vector.
    const auto noErrors = analyzer.getTopErrors(result, 0);

    if (!noErrors.empty()) {
        return 14;
    }

    return 0;
}
