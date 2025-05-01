#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "discordium/types/utils/snowflake.hpp"

struct VoiceState {
    Snowflake guildId;
    Snowflake channelId;
    Snowflake userId;
    bool deaf = false;
    bool mute = false;
    bool selfDeaf = false;
    bool selfMute = false;
    bool selfStream = false;
    bool selfVideo = false;
    bool suppress = false;

    static VoiceState fromJson(const nlohmann::json& j) {
        VoiceState v;
        v.guildId = Snowflake(j.value("guild_id", ""));
        v.channelId = Snowflake(j.value("channel_id", ""));
        v.userId = Snowflake(j.value("user_id", ""));
        v.deaf = j.value("deaf", false);
        v.mute = j.value("mute", false);
        v.selfDeaf = j.value("self_deaf", false);
        v.selfMute = j.value("self_mute", false);
        v.selfStream = j.value("self_stream", false);
        v.selfVideo = j.value("self_video", false);
        v.suppress = j.value("suppress", false);
        return v;
    }
};