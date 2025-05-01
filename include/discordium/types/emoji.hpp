#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "discordium/types/utils/snowflake.hpp"
#include "discordium/types/user.hpp"

struct Emoji {
    Snowflake id;
    std::string name;
    std::vector<Snowflake> roles;
    User user;
    bool requireColons;
    bool managed;
    bool animated;
    bool available;

    Emoji();
    static Emoji fromJson(const nlohmann::json& j);
};