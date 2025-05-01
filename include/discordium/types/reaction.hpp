#pragma once

#include <nlohmann/json.hpp>
#include "discordium/types/emoji.hpp"

struct Reaction {
    int count;
    bool me;
    Emoji emoji;

    static Reaction fromJson(const nlohmann::json& j);
};
