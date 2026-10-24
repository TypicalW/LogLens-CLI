#pragma once

#include "log_entry.hpp"
#include "parse_error.hpp"

#include <variant>

using ParseResult = std::variant<LogEntry, ParseError>;
