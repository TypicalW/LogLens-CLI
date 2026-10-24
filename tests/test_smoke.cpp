#include "log_entry.hpp"

int main() {
    LogEntry entry{
        "2026-10-24 10:30:15",
        LogLevel::ERROR,
        "Database connection timeout"
    };

    if (entry.timestamp != "2026-10-24 10:30:15") {
        return 1;
    }

    if (entry.level != LogLevel::ERROR) {
        return 1;
    }

    if (entry.message != "Database connection timeout") {
        return 1;
    }

    return 0;
}
