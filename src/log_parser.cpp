#include "log_parser.hpp"

#include <regex>
#include <string>

ParseResult LogParser::parse(const std::string& line) const {
    static const std::regex pattern(
        R"(^(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}) \[(DEBUG|INFO|WARN|ERROR)\] (.+)$)"
    );
    //god i hate regex, thank you ClaudeGPT

    std::smatch matches;

    if (!std::regex_match(line, matches, pattern)) {
        return ParseError{"Malformed log entry"};
    }

    const std::string timestamp = matches[1].str();
    const std::string levelText = matches[2].str();
    const std::string message = matches[3].str();

    LogLevel level;

    if (levelText == "DEBUG") {
        level = LogLevel::DEBUG;
    } else if (levelText == "INFO") {
        level = LogLevel::INFO;
    } else if (levelText == "WARN") {
        level = LogLevel::WARN;
    } else {
        level = LogLevel::ERROR;
    }

    return LogEntry(timestamp, level, message);
}
