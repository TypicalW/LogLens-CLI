#include "cli_parser.hpp"

#include <limits>
#include <stdexcept>
#include <string>

namespace {

bool isValidLevel(const std::string& level) {
    return level == "DEBUG" ||
           level == "INFO"  ||
           level == "WARN"  ||
           level == "ERROR";
}

LogLevel toLogLevel(const std::string& level) {
    if (level == "DEBUG") return LogLevel::DEBUG;
    if (level == "INFO")  return LogLevel::INFO;
    if (level == "WARN")  return LogLevel::WARN;
    return LogLevel::ERROR;
}

} // namespace

CliParseResult CliParser::parse(int argc, char* argv[]) const {
    CliOptions options;

    // 1. Check whether help was requested.
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--help") {
            options.showHelp = true;
            return options;
        }
    }

    // 2. Validate that a command was supplied.
    if (argc < 2) {
        return std::string(
            "Missing command. Use 'loglens --help' for usage."
        );
    }

    options.command = argv[1];

    if (options.command != "analyze") {
        return std::string(
            "Unknown command: " + options.command
        );
    }

    // 3. Validate that a file path was supplied.
    if (argc < 3) {
        return std::string(
            "Missing file path. Usage: loglens analyze <file>"
        );
    }

    options.filePath = argv[2];

    // 4. Parse optional flags.
    for (int i = 3; i < argc; ++i) {
        const std::string argument = argv[i];

        if (argument == "--level") {
            if (i + 1 >= argc) {
                return std::string(
                    "Missing value for --level"
                );
            }

            const std::string level = argv[++i];

            if (!isValidLevel(level)) {
                return std::string(
                    "Invalid severity level: " + level +
                    ". Expected DEBUG, INFO, WARN, or ERROR."
                );
            }

            options.filterOptions.level = toLogLevel(level);
        }
        else if (argument == "--keyword") {
            if (i + 1 >= argc) {
                return std::string(
                    "Missing value for --keyword"
                );
            }

            options.filterOptions.keyword = argv[++i];
        }
        else if (argument == "--top-errors") {
            if (i + 1 >= argc) {
                return std::string(
                    "Missing value for --top-errors"
                );
            }

            const std::string value = argv[++i];

            // Reject empty values, negatives, and non-numeric input.
            if (value.empty() ||
                value.front() == '-' ||
                value.find_first_not_of("0123456789") !=
                    std::string::npos) {
                return std::string(
                    "Invalid value for --top-errors: " + value
                );
            }

            try {
                std::size_t parsedCharacters = 0;
                const unsigned long long count =
                    std::stoull(value, &parsedCharacters);

                if (parsedCharacters != value.size() ||
                    count > std::numeric_limits<std::size_t>::max()) {
                    return std::string(
                        "Invalid value for --top-errors: " + value
                    );
                }

                options.topErrors = static_cast<std::size_t>(count);
            }
            catch (const std::exception&) {
                return std::string(
                    "Invalid value for --top-errors: " + value
                );
            }
        }
        else {
            return std::string(
                "Unknown option: " + argument
            );
        }
    }

    return options;
}