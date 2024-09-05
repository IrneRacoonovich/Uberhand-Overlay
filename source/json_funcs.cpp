#include "json_funcs.hpp"

#include "debug_funcs.hpp"

#include <jansson.h>
#include <sys/stat.h>

#include <memory>
#include <string>

struct FileCloser {
    void operator()(FILE* file) const
    {
        if (file) {
            fclose(file);
        }
    }
};

SafeJson readJsonFromFile(const std::string& filePath)
{
    // Check if the file exists
    struct stat fileStat;
    if (stat(filePath.c_str(), &fileStat) != 0) {
        log("ERROR: readJsonFromFile: failed to get stat for file \"%s\"", filePath.c_str());
        return nullptr;
    }

    // Open the file
    std::unique_ptr<FILE, FileCloser> file(fopen(filePath.c_str(), "r"));
    if (!file) {
        log("ERROR: readJsonFromFile: failed to open file \"%s\"", filePath.c_str());
        return nullptr;
    }

    json_error_t error;
    json_t* root = json_loadf(file.get(), JSON_DECODE_ANY, &error);
    if (!root) {
        log("ERROR: readJsonFromFile: failed to load file as json \"%s\"", filePath.c_str());
        return nullptr;
    }

    return root;
}
