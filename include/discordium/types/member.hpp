#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "discordium/types/utils/snowflake.hpp"
#include "discordium/types/user.hpp"

struct Member {
    User user;
    std::string nick;
    std::vector<Snowflake> roles;
    std::string joinedAt;
    std::string premiumSince;
    bool deaf;
    bool mute;
    bool pending;
    std::string permissions;

    Member();
    static Member fromJson(const nlohmann::json& j);
};