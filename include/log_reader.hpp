
#pragma once

#include "log_reader_result.hpp"

#include <string>

class LogReader {
public:
    LogReadResult read(const std::string& filePath) const;
};
