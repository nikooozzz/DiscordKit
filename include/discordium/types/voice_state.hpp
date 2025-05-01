#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "discordium/types/utils/snowflake.hpp"
#include "discordium/types/member.hpp"

struct VoiceState {
    Snowflake guildId;
    Snowflake channelId;
    Snowflake userId;
    Member member;
    std::string sessionId;
    bool deaf;
    bool mute;
    bool selfDeaf;
    bool selfMute;
    bool selfStream;
    bool selfVideo;
    bool suppress;
    std::string requestToSpeakTimestamp;

    static VoiceState fromJson(const nlohmann::json& j);
}; 