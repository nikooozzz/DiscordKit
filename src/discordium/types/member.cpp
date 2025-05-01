#include "discordium/types/member.hpp"

Member::Member() {
    nick.reserve(32);
    roles.reserve(10);
}

Member Member::fromJson(const nlohmann::json& j) {
    Member m;
    m.user = User::fromJson(j.at("user"));
    m.nick = j.value("nick", "");
    m.roles = std::vector<Snowflake>();
    if (j.contains("roles") && j["roles"].is_array()) {
        for (const auto& role : j["roles"]) {
            m.roles.push_back(Snowflake(role.get<std::string>()));
        }
    }
    m.joinedAt = j.value("joined_at", "");
    m.premiumSince = j.value("premium_since", "");
    m.deaf = j.value("deaf", false);
    m.mute = j.value("mute", false);
    m.pending = j.value("pending", false);
    m.permissions = j.value("permissions", "");
    return m;
} 