#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "discordium/types/utils/snowflake.hpp"
#include "discordium/types/member.hpp"
#include "discordium/types/channel.hpp"
#include "discordium/types/role.hpp"
#include "discordium/types/emoji.hpp"

struct Guild {
    Snowflake id;
    std::string name;
    std::string icon;
    std::string description;
    std::string splash;
    std::string discoverySplash;
    Snowflake ownerId;
    std::string region;
    Snowflake afkChannelId;
    int afkTimeout;
    int verificationLevel;
    int defaultMessageNotifications;
    int explicitContentFilter;
    int mfaLevel;
    Snowflake applicationId;
    Snowflake systemChannelId;
    int systemChannelFlags;
    Snowflake rulesChannelId;
    std::string joinedAt;
    bool large;
    bool unavailable;
    int memberCount;
    int maxPresences;
    int maxMembers;
    std::string vanityUrlCode;
    int premiumTier;
    int premiumSubscriptionCount;
    std::string preferredLocale;
    Snowflake publicUpdatesChannelId;
    int maxVideoChannelUsers;
    int approximateMemberCount;
    int approximatePresenceCount;
    nlohmann::json welcomeScreen;
    int nsfwLevel;
    nlohmann::json stageInstances;
    nlohmann::json stickers;
    nlohmann::json scheduledEvents;
    bool premiumProgressBarEnabled;

    std::vector<Member> members;
    std::vector<Channel> channels;
    std::vector<Role> roles;
    std::vector<Emoji> emojis;

    Guild();
    static Guild fromJson(const nlohmann::json& j);
};