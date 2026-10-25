#pragma once

#include "cli_options.hpp"

#include <string>
#include <variant>

using CliParseResult = std::variant<CliOptions, std::string>;

class CliParser {
public:
    CliParseResult parse(int argc, char* argv[]) const;
};