#pragma once

#ifdef USE_PROFILER

#include <array>
#include <chrono>
#include <cstring>
#include <fstream>
#include <thread>

#define PROFILER_BUFFER_SIZE 100
#define PROFILER_DUMP_FILE "/prof.out"

#define PROFILE_ADD(X)                                                                           \
    {                                                                                            \
        __Profiler::Frame frame {                                                                \
            std::hash<std::thread::id> {}(std::this_thread::get_id()),                           \
            (size_t)std::chrono::steady_clock::now().time_since_epoch().count(),                 \
            (X),                                                                                 \
            { 0 }                                                                                \
        };                                                                                       \
        std::strncpy(frame.name, __Profiler::funcName(__PRETTY_FUNCTION__), sizeof(frame.name)); \
        *__Profiler::profile_buffer_it = frame;                                                  \
        __Profiler::profile_buffer_it++;                                                         \
        /* need one frame for registering dump_buffer to the buffer as well */                   \
        if (__Profiler::profile_buffer_it + 1 == __Profiler::profile_buffer.end()) {             \
            __Profiler::dump_buffer();                                                           \
        }                                                                                        \
    }

#define PROFILE_ENTER PROFILE_ADD(true)
#define PROFILE_EXIT PROFILE_ADD(false)

#define PROFILER_INIT                                                                                                       \
    std::array<__Profiler::Frame, __Profiler::BufferSize> __Profiler::profile_buffer = { 0 };                               \
    std::array<__Profiler::Frame, __Profiler::BufferSize>::iterator __Profiler::profile_buffer_it = profile_buffer.begin(); \
    std::ofstream __Profiler::profile_file;

#define PROFILER_OPEN_FILE \
    __Profiler::profile_file = std::ofstream(__Profiler::DumpFile, std::ios_base::trunc);

namespace __Profiler {

constexpr size_t BufferSize { PROFILER_BUFFER_SIZE };
constexpr const char* DumpFile { PROFILER_DUMP_FILE };

struct Frame {
    size_t thread_id { 0 };
    size_t timestamp { 0 };
    bool enter { false };
    char name[111] { 0 };
};
static_assert(sizeof(Frame) == 128U);

extern std::array<Frame, PROFILER_BUFFER_SIZE> profile_buffer;
extern std::array<Frame, PROFILER_BUFFER_SIZE>::iterator profile_buffer_it;
extern std::ofstream profile_file;

// input __PRETTY_FUNCTION__
constexpr const char* funcName(const char* pretty_function)
{
    const char* pos = pretty_function;
    for (const char* it = pretty_function; *it != 0; it++) {
        if (*it == ' ')
            pos = it + 1;
        if (*it == '(') // reached the parameter list
            break;
    }
    return pos;
}

inline void dump_buffer()
{
    PROFILE_ENTER
    profile_file.write((const char*)profile_buffer.data(), sizeof(profile_buffer));
    profile_buffer_it = profile_buffer.begin();
    profile_buffer.fill({ 0 });
    PROFILE_EXIT
}

} // namespace __Profiler

#else

#define PROFILE_ENTER
#define PROFILE_EXIT
#define PROFILER_INIT

#endif
