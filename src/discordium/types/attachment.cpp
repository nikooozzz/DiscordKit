#include "discordium/types/attachment.hpp"

Attachment Attachment::fromJson(const nlohmann::json& j) {
    Attachment a;
    a.id = Snowflake(j.at("id").get<std::string>());
    a.filename = j.at("filename").get<std::string>();
    a.description = j.value("description", "");
    a.contentType = j.value("content_type", "");
    a.size = j.value("size", 0);
    a.url = j.at("url").get<std::string>();
    a.proxyUrl = j.at("proxy_url").get<std::string>();
    a.height = j.value("height", 0);
    a.width = j.value("width", 0);
    a.ephemeral = j.value("ephemeral", false);
    return a;
} 