#include "discordium/types/message.hpp"

Message::Message() {
    mentionedUsers.reserve(5);
    roleMentions.reserve(3);
    attachments.reserve(2);
    embeds.reserve(1);
}

bool Message::mentionsUser(const Snowflake& userId) const {
    return std::find(mentionedUsers.begin(), mentionedUsers.end(), userId) != mentionedUsers.end();
}

Message Message::fromJson(const nlohmann::json& j) {
    Message m;
    m.id = Snowflake(j.at("id").get<std::string>());
    m.channelId = Snowflake(j.at("channel_id").get<std::string>());
    m.guildId = Snowflake(j.value("guild_id", ""));
    m.author = User::fromJson(j.at("author"));
    m.content = j.value("content", "");

    m.timestamp = Timestamp(j.value("timestamp", ""));
    m.editedTimestamp = Timestamp(j.value("edited_timestamp", ""));

    m.tts = j.value("tts", false);
    m.mentionEveryone = j.value("mention_everyone", false);

    if (j.contains("mentions") && j["mentions"].is_array()) {
        const auto& mentions = j["mentions"];
        m.mentionedUsers.reserve(mentions.size());
        for (const auto& mention : mentions) {
            m.mentionedUsers.push_back(User::fromJson(mention));
        }
    }

    if (j.contains("mention_roles") && j["mention_roles"].is_array()) {
        const auto& roles = j["mention_roles"];
        m.roleMentions.reserve(roles.size());
        for (const auto& role : roles) {
            m.roleMentions.push_back(Snowflake(role.get<std::string>()));
        }
    }

    if (j.contains("attachments") && j["attachments"].is_array()) {
        const auto& atts = j["attachments"];
        m.attachments.reserve(atts.size());
        for (const auto& att : atts) {
            m.attachments.push_back(Attachment::fromJson(att));
        }
    }

    if (j.contains("embeds") && j["embeds"].is_array()) {
        const auto& embs = j["embeds"];
        m.embeds.reserve(embs.size());
        for (const auto& emb : embs) {
            m.embeds.push_back(Embed::fromJson(emb));
        }
    }

    m.pinned = j.value("pinned", false);
    m.isBot = m.author.bot;

    return m;
} 