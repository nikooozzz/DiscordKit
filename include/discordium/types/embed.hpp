#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "discordium/types/utils/time.hpp"

struct Embed {
  std::string title;
  std::string description;
  std::string url;
  Time timestamp;
  int color = 0;

  struct Footer {
    std::string text;
    std::string iconUrl;
  } footer;

  struct Image {
    std::string url;
    std::string proxyUrl;
    int height = 0;
    int width = 0;
  } image;

  bool isEmpty() const {
      return title.empty() && description.empty() && url.empty() && timestamp.isEmpty();
  }

  bool hasImage() const {
      return !image.url.empty();
  }

  static Embed fromJson(const nlohmann::json& j) {
      Embed e;
      e.title = j.value("title", "");
      e.description = j.value("description", "");
      e.url = j.value("url", "");
      e.timestamp = Time(j.value("timestamp", ""));
      e.color = j.value("color", 0);

      if (j.contains("footer")) {
          const auto& f = j["footer"];
          e.footer.text = f.value("text", "");
          e.footer.iconUrl = f.value("icon_url", "");
      }

      if (j.contains("image")) {
          const auto& i = j["image"];
          e.image.url = i.value("url", "");
          e.image.proxyUrl = i.value("proxy_url", "");
          e.image.height = i.value("height", 0);
          e.image.width = i.value("width", 0);
      }

      return e;
  }
};