#pragma once
#include <string>

struct Asset {
    std::string hash;
    std::string format;
    bool animated;

    Asset(const std::string& hash = "", const std::string& format = "png", bool animated = false)
        : hash(hash), format(format), animated(animated) {}

    std::string getUrl(const std::string& baseUrl, const std::string& id) const {
        if (hash.empty()) return "";
        std::string ext = animated ? "gif" : format;
        return baseUrl + "/" + id + "/" + hash + "." + ext;
    }

    bool isEmpty() const {
        return hash.empty();
    }
}; 