#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "discordium/types/utils/snowflake.hpp"
#include "discordium/types/user.hpp"
#include "discordium/types/activity.hpp"

struct Presence {
    User user;
    Snowflake guildId;
    std::string status;
    std::vector<Activity> activities;
    nlohmann::json clientStatus;

    static Presence fromJson(const nlohmann::json& j);
};