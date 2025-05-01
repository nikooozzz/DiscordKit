#include "discordium/types/user.hpp"

User User::fetchUserById(const Snowflake& userId) {
    // TODO: Implement actual API call
    // This is a placeholder that will be replaced with actual API implementation
    User u;
    u.id = userId;
    return u;
}

std::string User::getAvatarUrl() const {
    return avatar.getUrl("https://cdn.discordapp.com/avatars", std::to_string(id));
}

std::string User::getMention() const {
    return "<@" + std::to_string(id) + ">";
}

User User::fromJson(std::string_view json_str) {
    auto j = nlohmann::json::parse(json_str);
    return fromJson(j);
}

User User::fromJson(const nlohmann::json& j) {
    User u;
    u.id = Snowflake(j.at("id").get<std::string>());
    u.username = j.at("username").get<std::string>();
    u.globalName = j.value("global_name", "");
    u.avatar = Asset(j.value("avatar", ""), "png", j.value("avatar_animated", false));
    u.bot = j.value("bot", false);
    return u;
} 