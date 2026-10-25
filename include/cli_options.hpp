#pragma once

#include "log_filter_options.hpp"

#include <cstddef>
#include <optional>
#include <string>

struct CliOptions {
    std::string command;
    std::string filePath;

    LogFilterOptions filterOptions;

    std::optional<std::size_t> topErrors;

    bool showHelp = false;
};