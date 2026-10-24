
#pragma once

#include "analyzer_result.hpp"
#include "log_reader_result.hpp"

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

class LogAnalyzer {
public:
    LogAnalyzerResult analyze(const LogReadResult& input) const;

    std::vector<std::pair<std::string, std::size_t>>
    getTopErrors(
        const LogAnalyzerResult& result,
        std::size_t limit
    ) const;
};
