#pragma once

#include "parse_result.hpp"

#include <string>

class LogParser {
public:
    ParseResult parse(const std::string& line) const;
};
