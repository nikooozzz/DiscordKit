#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "discordium/types/utils/snowflake.hpp"

struct Attachment {
    Snowflake id;
    std::string filename;
    std::string description;
    std::string contentType;
    size_t size;
    std::string url;
    std::string proxyUrl;
    int height;
    int width;
    bool ephemeral;

    static Attachment fromJson(const nlohmann::json& j);
};