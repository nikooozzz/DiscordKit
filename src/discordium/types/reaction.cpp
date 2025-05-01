#include "discordium/types/reaction.hpp"

Reaction Reaction::fromJson(const nlohmann::json& j) {
    Reaction r;
    r.count = j.value("count", 0);
    r.me = j.value("me", false);
    r.emoji = Emoji::fromJson(j.at("emoji"));
    return r;
} 