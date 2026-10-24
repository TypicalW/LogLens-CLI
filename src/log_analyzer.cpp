
#include "log_analyzer.hpp"

#include <algorithm>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

LogAnalyzerResult LogAnalyzer::analyze(
    const LogReadResult& input
) const {
    LogAnalyzerResult result;

    // Copy information already collected by LogReader.
    result.totalEntries = input.entries.size();
    result.malformedLines = input.malformedLines;

    // Count severity levels and error-message frequencies.
    for (const LogEntry& entry : input.entries) {
        ++result.levelCounts[entry.getLevel()];

        if (entry.getLevel() == LogLevel::ERROR) {
            ++result.errorFrequencies[entry.getMessage()];
        }
    }

    return result;
}

std::vector<std::pair<std::string, std::size_t>>
LogAnalyzer::getTopErrors(
    const LogAnalyzerResult& result,
    std::size_t limit
) const {
    // Convert the map into a vector so it can be ranked.
    std::vector<std::pair<std::string, std::size_t>> errors(
        result.errorFrequencies.begin(),
        result.errorFrequencies.end()
    );

    // Sort by descending frequency, then alphabetically.
    std::sort(
        errors.begin(),
        errors.end(),
        [](const auto& a, const auto& b) {
            if (a.second != b.second) {
                return a.second > b.second;
            }

            return a.first < b.first;
        }
    );

    // Keep at most the requested number of results.
    if (errors.size() > limit) {
        errors.resize(limit);
    }

    return errors;
}
