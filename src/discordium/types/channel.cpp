#include "discordium/types/channel.hpp"

Channel::Channel() {
    name.reserve(32);
    topic.reserve(1024);
}

std::string Channel::getMention() const {
    return "<#" + std::to_string(id) + ">";
}

Channel Channel::fromJson(const nlohmann::json& j) {
    Channel c;
    c.id = Snowflake(j.at("id").get<std::string>());
    c.guildId = Snowflake(j.value("guild_id", ""));
    c.type = static_cast<ChannelType>(j.at("type").get<int>());
    
    if (auto name_it = j.find("name"); name_it != j.end()) {
        c.name = name_it->get<std::string>();
    }
    
    if (auto topic_it = j.find("topic"); topic_it != j.end()) {
        c.topic = topic_it->get<std::string>();
    }
    
    c.position = j.value("position", 0);
    c.nsfw = j.value("nsfw", false);
    c.parentId = Snowflake(j.value("parent_id", ""));
    return c;
} 