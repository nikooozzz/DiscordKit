#include "discordium/types/voice_state.hpp"

VoiceState VoiceState::fromJson(const nlohmann::json& j) {
    VoiceState vs;
    vs.guildId = Snowflake(j.value("guild_id", ""));
    vs.channelId = Snowflake(j.value("channel_id", ""));
    vs.userId = Snowflake(j.at("user_id").get<std::string>());
    vs.member = j.contains("member") ? Member::fromJson(j["member"]) : Member();
    vs.sessionId = j.at("session_id").get<std::string>();
    vs.deaf = j.value("deaf", false);
    vs.mute = j.value("mute", false);
    vs.selfDeaf = j.value("self_deaf", false);
    vs.selfMute = j.value("self_mute", false);
    vs.selfStream = j.value("self_stream", false);
    vs.selfVideo = j.value("self_video", false);
    vs.suppress = j.value("suppress", false);
    vs.requestToSpeakTimestamp = j.value("request_to_speak_timestamp", "");
    return vs;
} 