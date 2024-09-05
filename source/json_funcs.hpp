#pragma once

#include <jansson.h>

#include <string>

class SafeJson {
public:
    SafeJson(json_t* json)
        : _json(json)
    {
    }
    SafeJson(const SafeJson& rh)
        : _json(rh._json)
    {
        json_incref(_json);
    };
    SafeJson(SafeJson&& rh)
        : _json(rh._json)
    {
        rh._json = nullptr;
    }
    ~SafeJson()
    {
        if (_json) {
            json_decref(_json);
        }
    }
    operator json_t*() { return _json; }
    operator bool() { return nullptr != _json; }
    auto operator->() { return _json; }

private:
    json_t* _json { nullptr };
};

SafeJson readJsonFromFile(const std::string& filePath);
