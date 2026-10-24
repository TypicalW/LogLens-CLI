
#include "log_reader.hpp"

#include "log_parser.hpp"

#include <fstream>
#include <stdexcept>
#include <string>
#include <variant>

LogReadResult LogReader::read(const std::string& filePath) const {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    LogParser parser;
    LogReadResult result;

    std::string line;

    while (std::getline(file, line)) {
        ParseResult parsed = parser.parse(line);

        if (std::holds_alternative<LogEntry>(parsed)) {
            result.entries.push_back(
                std::get<LogEntry>(parsed)
            );
        } else {
            ++result.malformedLines;
        }
    }

    if (file.bad()) {
        throw std::runtime_error("Error while reading file: " + filePath);
    }

    return result;
}
