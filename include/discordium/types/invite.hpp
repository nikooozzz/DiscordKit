#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "discordium/types/utils/snowflake.hpp"

struct Invite {
    std::string code;
    Snowflake guildId;
    Snowflake channelId;
    int uses = 0;
    int maxUses = 0;
    int maxAge = 0;
    bool temporary = false;
    Snowflake inviterId;

    static Invite fromJson(const nlohmann::json& j) {
        Invite i;
        i.code = j.at("code").get<std::string>();
        i.guildId = Snowflake(j.value("guild", nlohmann::json::object()).value("id", ""));
        i.channelId = Snowflake(j.value("channel", nlohmann::json::object()).value("id", ""));
        i.uses = j.value("uses", 0);
        i.maxUses = j.value("max_uses", 0);
        i.maxAge = j.value("max_age", 0);
        i.temporary = j.value("temporary", false);
        i.inviterId = Snowflake(j.value("inviter", nlohmann::json::object()).value("id", ""));
        return i;
    }
};