#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "user.hpp"
#include "role.hpp"
#include "attachment.hpp"
#include "embed.hpp"
#include "discordium/types/utils/snowflake.hpp"
#include "discordium/types/utils/time.hpp"

struct Message {
  Snowflake id;
  Snowflake channelId;
  Snowflake guildId;

  User author;
  std::string content;

  Timestamp timestamp;  
  Timestamp editedTimestamp; 

  bool tts = false;
  bool mentionEveryone = false;
  bool pinned = false;
  bool isBot = false;

  std::vector<User> mentionedUsers;
  std::vector<Snowflake> roleMentions;

  std::vector<Attachment> attachments;
  std::vector<Embed> embeds;

  Message();
  bool mentionsUser(const Snowflake& userId) const;
  static Message fromJson(const nlohmann::json& j);
};