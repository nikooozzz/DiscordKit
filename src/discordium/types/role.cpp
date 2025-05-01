#include "discordium/types/role.hpp"

Role::Role() {
    name.reserve(32);
}

std::string Role::getMention() const {
    return "<@&" + std::to_string(id) + ">";
}

Role Role::fromJson(const nlohmann::json& j) {
    Role r;
    r.id = Snowflake(j.at("id").get<std::string>());
    r.name = j.at("name").get<std::string>();
    r.color = j.value("color", 0);
    r.hoist = j.value("hoist", false);
    r.position = j.value("position", 0);
    r.permissions = j.value("permissions", 0);
    r.managed = j.value("managed", false);
    r.mentionable = j.value("mentionable", false);
    return r;
} 