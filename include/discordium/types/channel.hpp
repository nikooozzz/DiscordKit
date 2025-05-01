#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "discordium/types/utils/snowflake.hpp"
#include "discordium/types/utils/channel_type.hpp"

struct Channel {
  Snowflake id;
  Snowflake guildId;
  ChannelType type;
  std::string name;
  std::string topic;
  int position = 0;
  bool nsfw = false;
  Snowflake parentId;

  Channel();
  std::string getMention() const;
  static Channel fromJson(const nlohmann::json& j);
};