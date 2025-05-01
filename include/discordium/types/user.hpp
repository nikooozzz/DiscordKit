#pragma once
#include <string>
#include <string_view>
#include <nlohmann/json.hpp>
#include "discordium/types/utils/snowflake.hpp"
#include "discordium/types/utils/asset.hpp"

struct User {
  public:
  Snowflake id;
  std::string username;
  std::string globalName;
  Asset avatar;
  bool bot = false;

  // TODO: User::fetchUserById implementation. Requires API and cache implementations, or a placeholder method
  User fetchUserById(const Snowflake& userId);

  std::string getAvatarUrl() const;
  std::string getMention() const;

  static User fromJson(std::string_view json_str);
  static User fromJson(const nlohmann::json& j);
};