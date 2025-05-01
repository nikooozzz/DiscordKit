#include "discordium/types/emoji.hpp"

Emoji::Emoji() {
    name.reserve(32);
}

Emoji Emoji::fromJson(const nlohmann::json& j) {
    Emoji e;
    e.id = Snowflake(j.value("id", ""));
    e.name = j.value("name", "");
    e.roles = std::vector<Snowflake>();
    if (j.contains("roles") && j["roles"].is_array()) {
        for (const auto& role : j["roles"]) {
            e.roles.push_back(Snowflake(role.get<std::string>()));
        }
    }
    e.user = j.contains("user") ? User::fromJson(j["user"]) : User();
    e.requireColons = j.value("require_colons", false);
    e.managed = j.value("managed", false);
    e.animated = j.value("animated", false);
    e.available = j.value("available", false);
    return e;
} 