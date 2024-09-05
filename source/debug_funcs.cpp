#include "debug_funcs.hpp"

#include <switch.h> // should be <switch/services/time.h> but this breaks linking

#include <algorithm>
#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <ctime>

constexpr const char* logPath = "sdmc:/config/uberhand/log.txt";

void log(const char* format, ...) noexcept
{
    static char logTimeBuffer[std::size("yyyy-mm-dd hh:mm:ss")] { 0 };
    FILE* logFile = fopen(logPath, "a");
    if (logFile == nullptr) {
        fprintf(stderr, "Failed to open log file: %s", logPath);
        return;
    }
    u64 currentTime;
    timeGetCurrentTime(TimeType_NetworkSystemClock, &currentTime);
    tm* localTime = std::localtime((std::time_t*)(&currentTime));
    std::strftime(logTimeBuffer, sizeof(logTimeBuffer), "%F %T", localTime);

    fputc('[', logFile);
    fputs(logTimeBuffer, logFile);
    fputc(']', logFile);
    fputc(' ', logFile);
    va_list args;
    va_start(args, format);
    vfprintf(logFile, format, args);
    va_end(args);
    fputc('\n', logFile);
    fclose(logFile);
}