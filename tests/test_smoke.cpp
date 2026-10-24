
#include "log_parser.hpp"

#include <variant>

int main() {
    LogParser parser;

    // Test valid input.
    ParseResult valid = parser.parse(
        "2026-10-24 10:30:15 [ERROR] Database connection timeout"
    );

    if (!std::holds_alternative<LogEntry>(valid)) {
        return 1;
    }

    const LogEntry& entry = std::get<LogEntry>(valid);

    if (entry.getLevel() != LogLevel::ERROR) {
        return 2;
    }

    if (entry.getMessage() != "Database connection timeout") {
        return 3;
    }

    // Test malformed input.
    ParseResult invalid = parser.parse("This is not a valid log entry");

    if (!std::holds_alternative<ParseError>(invalid)) {
        return 4;
    }

    const ParseError& error = std::get<ParseError>(invalid);

    if (error.message.empty()) {
        return 5;
    }

    return 0;
}
