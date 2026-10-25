#include "cli_parser.hpp"
#include "log_reader.hpp"
#include "log_analyzer.hpp"
#include "log_filter.hpp"

#include <exception>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

namespace {

std::string levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO:  return "INFO";
        case LogLevel::WARN:  return "WARN";
        case LogLevel::ERROR: return "ERROR";
    }

    return "UNKNOWN";
}

void printHelp() {
    std::cout
        << "LogLens - Log Analysis CLI\n\n"
        << "Usage:\n"
        << "  loglens analyze <file> [options]\n"
        << "  loglens --help\n\n"
        << "Options:\n"
        << "  --level <LEVEL>       Filter by DEBUG, INFO, WARN, or ERROR\n"
        << "  --keyword <TEXT>      Filter messages by case-insensitive keyword\n"
        << "  --top-errors <N>      Show the N most frequent error messages\n"
        << "  --help                Display this help message\n";
}

void printSummary(const LogAnalyzerResult& result) {
    std::cout << "\n=== Log Summary ===\n";

    std::cout << "Valid entries:    "
              << result.totalEntries << '\n';

    std::cout << "Malformed lines:  "
              << result.malformedLines << '\n';

    std::cout << "\nSeverity counts:\n";

    const LogLevel levels[] = {
        LogLevel::DEBUG,
        LogLevel::INFO,
        LogLevel::WARN,
        LogLevel::ERROR
    };

    for (LogLevel level : levels) {
        auto it = result.levelCounts.find(level);

        const std::size_t count =
            (it != result.levelCounts.end()) ? it->second : 0;

        std::cout << "  " << levelToString(level)
                  << ": " << count << '\n';
    }
}

void printEntries(const std::vector<LogEntry>& entries) {
    std::cout << "\n=== Matching Log Entries ===\n";

    if (entries.empty()) {
        std::cout << "No entries matched the supplied filters.\n";
        return;
    }

    for (const LogEntry& entry : entries) {
        std::cout << entry.getTimestamp()
                  << " [" << levelToString(entry.getLevel()) << "] "
                  << entry.getMessage() << '\n';
    }

    std::cout << "Matched entries: " << entries.size() << '\n';
}

void printTopErrors(
    const LogAnalyzer& analyzer,
    const LogAnalyzerResult& result,
    std::size_t limit
) {
    std::cout << "\n=== Top " << limit << " Error Messages ===\n";

    const auto errors = analyzer.getTopErrors(result, limit);

    if (errors.empty()) {
        std::cout << "No error messages found.\n";
        return;
    }

    std::size_t rank = 1;

    for (const auto& error : errors) {
        std::cout << rank++ << ". "
                  << error.first
                  << " (occurred " << error.second << " times)\n";
    }
}

} // namespace

int main(int argc, char* argv[]) {
    CliParser cliParser;

    const CliParseResult parseResult =
        cliParser.parse(argc, argv);

    // Step 1: Handle parsing errors.
    if (const auto* error =
            std::get_if<std::string>(&parseResult)) {
        std::cerr << "Error: " << *error << '\n';
        std::cerr << "Use 'loglens --help' for usage.\n";
        return 1;
    }

    const CliOptions& options =
        std::get<CliOptions>(parseResult);

    // Step 2: Handle help.
    if (options.showHelp) {
        printHelp();
        return 0;
    }

    try {
        // Step 3: Read and parse the log file.
        LogReader reader;
        const LogReadResult readResult =
            reader.read(options.filePath);

        // Step 4: Analyze all valid entries.
        LogAnalyzer analyzer;
        const LogAnalyzerResult analysis =
            analyzer.analyze(readResult);

        // The summary is always printed.
        printSummary(analysis);

        // Step 5: Apply filters if requested.
        const bool filtersRequested =
            options.filterOptions.level.has_value() ||
            !options.filterOptions.keyword.empty();

        if (filtersRequested) {
            LogFilter filter;

            const std::vector<LogEntry> filteredEntries =
                filter.filter(
                    readResult.entries,
                    options.filterOptions
                );

            printEntries(filteredEntries);
        }

        // Step 6: Print top-N errors if requested.
        if (options.topErrors.has_value()) {
            printTopErrors(
                analyzer,
                analysis,
                options.topErrors.value()
            );
        }

        return 0;
    }
    catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}