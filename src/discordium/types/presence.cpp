#include "discordium/types/presence.hpp"

Presence Presence::fromJson(const nlohmann::json& j) {
    Presence p;
    p.user = User::fromJson(j.at("user"));
    p.guildId = Snowflake(j.value("guild_id", ""));
    p.status = j.value("status", "");
    p.activities = std::vector<Activity>();
    if (j.contains("activities") && j["activities"].is_array()) {
        for (const auto& activity : j["activities"]) {
            p.activities.push_back(Activity::fromJson(activity));
        }
    }
    p.clientStatus = j.value("client_status", nlohmann::json::object());
    return p;
} 