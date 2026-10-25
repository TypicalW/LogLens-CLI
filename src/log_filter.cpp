#include "log_filter.hpp"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

namespace {

std::string toLower(std::string text) {
    std::transform(
        text.begin(),
        text.end(),
        text.begin(),
        [](unsigned char ch) {
            return static_cast<char>(std::tolower(ch));
        }
    );

    return text;
}

} // namespace

std::vector<LogEntry> LogFilter::filter(
    const std::vector<LogEntry>& entries,
    const LogFilterOptions& options
) const {
    std::vector<LogEntry> filteredEntries;

    const std::string keyword = toLower(options.keyword);

    for (const LogEntry& entry : entries) {
        // Condition 1: severity
        if (options.level.has_value() &&
            entry.getLevel() != options.level.value()) {
            continue;
        }

        // Condition 2: keyword
        if (!keyword.empty()) {
            const std::string message = toLower(entry.getMessage());

            if (message.find(keyword) == std::string::npos) {
                continue;
            }
        }

        // Reached here: every active condition matched.
        filteredEntries.push_back(entry);
    }

    return filteredEntries;
}