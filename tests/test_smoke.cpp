#include "log_entry.hpp"

int main() {
    LogEntry entry{
        "2026-10-24 10:30:15",
        LogLevel::ERROR,
        "Database connection timeout"
    };

    if(entry.getTimestamp()!="2026-10-24 10:30:15"){
        return 1;
    }
    if(entry.getLevel()!=LogLevel::ERROR){
        return 1;
    }
    if(entry.getMessage()!="Database connection timeout"){
        return 1;
    }
    return 0;
}
