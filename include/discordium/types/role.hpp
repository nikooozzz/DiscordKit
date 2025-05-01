#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "discordium/types/utils/snowflake.hpp"

struct Role {
    Snowflake id;
    std::string name;
    uint32_t color = 0;
    bool hoist = false;
    int position = 0;
    uint64_t permissions = 0;
    bool managed = false;
    bool mentionable = false;

    Role();
    std::string getMention() const;
    static Role fromJson(const nlohmann::json& j);
};