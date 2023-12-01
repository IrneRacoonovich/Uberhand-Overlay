#pragma once
#include <cstdio>
#include <time.h>

// uncomment to activate debug logging
// #define DEBUG

namespace {

    void log(const std::string& message) {
        FILE* file = fopen("sdmc:/config/uberhand/log.txt", "a");
        if (file != nullptr) {
            std::time_t currentTime = std::time(nullptr);
            const char* time = std::asctime(std::localtime(&currentTime));
            fprintf(file, "[%s] %s\n", time, message.c_str());
            fclose(file);
        }
    }

}

inline void logMessage(const std::string& message) {
    log(message);
}

inline void logInfo(const std::string& message) {
    log("[INFO] " + message);
}

inline void logError(const std::string& message) {
    log("[ERROR] " + message);
}

inline void logWarning(const std::string& message) {
    log("[WARN] " + message);
}

inline void logDebug(const std::string& message) {
#ifdef DEBUG
    log("[DEBUG] " + message);
#endif
}
