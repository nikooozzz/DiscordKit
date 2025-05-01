#include "discordium/types/guild.hpp"

Guild::Guild() {
    name.reserve(32);
    description.reserve(1024);
    members.reserve(100);
    channels.reserve(50);
    roles.reserve(20);
    emojis.reserve(50);
}

Guild Guild::fromJson(const nlohmann::json& j) {
    Guild g;
    g.id = Snowflake(j.at("id").get<std::string>());
    g.name = j.at("name").get<std::string>();
    g.icon = j.value("icon", "");
    g.description = j.value("description", "");
    g.splash = j.value("splash", "");
    g.discoverySplash = j.value("discovery_splash", "");
    g.ownerId = Snowflake(j.value("owner_id", ""));
    g.region = j.value("region", "");
    g.afkChannelId = Snowflake(j.value("afk_channel_id", ""));
    g.afkTimeout = j.value("afk_timeout", 0);
    g.verificationLevel = j.value("verification_level", 0);
    g.defaultMessageNotifications = j.value("default_message_notifications", 0);
    g.explicitContentFilter = j.value("explicit_content_filter", 0);
    g.mfaLevel = j.value("mfa_level", 0);
    g.applicationId = Snowflake(j.value("application_id", ""));
    g.systemChannelId = Snowflake(j.value("system_channel_id", ""));
    g.systemChannelFlags = j.value("system_channel_flags", 0);
    g.rulesChannelId = Snowflake(j.value("rules_channel_id", ""));
    g.joinedAt = j.value("joined_at", "");
    g.large = j.value("large", false);
    g.unavailable = j.value("unavailable", false);
    g.memberCount = j.value("member_count", 0);
    g.maxPresences = j.value("max_presences", 0);
    g.maxMembers = j.value("max_members", 0);
    g.vanityUrlCode = j.value("vanity_url_code", "");
    g.premiumTier = j.value("premium_tier", 0);
    g.premiumSubscriptionCount = j.value("premium_subscription_count", 0);
    g.preferredLocale = j.value("preferred_locale", "");
    g.publicUpdatesChannelId = Snowflake(j.value("public_updates_channel_id", ""));
    g.maxVideoChannelUsers = j.value("max_video_channel_users", 0);
    g.approximateMemberCount = j.value("approximate_member_count", 0);
    g.approximatePresenceCount = j.value("approximate_presence_count", 0);
    g.welcomeScreen = j.value("welcome_screen", nlohmann::json::object());
    g.nsfwLevel = j.value("nsfw_level", 0);
    g.stageInstances = j.value("stage_instances", nlohmann::json::array());
    g.stickers = j.value("stickers", nlohmann::json::array());
    g.scheduledEvents = j.value("scheduled_events", nlohmann::json::array());
    g.premiumProgressBarEnabled = j.value("premium_progress_bar_enabled", false);
    return g;
} 