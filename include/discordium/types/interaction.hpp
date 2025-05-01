#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "discordium/types/utils/snowflake.hpp"

struct Interaction {
  Snowflake id;
  std::string type;
  std::string commandName;
  Snowflake userId;
  std::string token;

  static Interaction fromJson(const nlohmann::json& j) {
      Interaction i;
      i.id = Snowflake(j.at("id").get<std::string>());
      i.type = j.at("type").get<std::string>();
      i.commandName = j.value("data", nlohmann::json::object()).value("name", "");
      i.userId = Snowflake(j.at("user").at("id").get<std::string>());
      i.token = j.at("token").get<std::string>();
      return i;
  }
};