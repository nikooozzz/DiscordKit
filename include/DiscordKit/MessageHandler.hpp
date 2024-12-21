//
// Created by Nikolai Käck on 2024-12-13.
//

#pragma once

#include <nlohmann/json.hpp>

#include "DiscordKit/Opcodes.hpp"
#include "WSClient.hpp"

class WSClient;
void handleHello();

/**
 * @brief Handler object for managing incoming messages from the Discord Websocket. Recieved in @link WSClient @endlink
 * but internal opcode handling and mapping happens here. */
class MessageHandler
{
public:
	MessageHandler(WSClient &parent) : parent(parent)
	{
		register_handler_(DiscordKit::opcodes::Gateway::HELLO, handleHello);
	};

	std::any handle(const std::string& msg)
	{
		auto func = get_handler_(msg).value();
		return func();
	};
private:
	std::optional<nlohmann::json> parse()
	{
		auto const json = nlohmann::json::parse(msg, nullptr, false);
		if (json.is_discarded()) return std::nullopt;
		return json;
	};

	/**
	 * @brief Checks a message and returns a method to run.
	 */
	static std::optional<std::function<void(const nlohmann::json &)>> get_handler_(const nlohmann::json& json)
	{
		auto opcode = static_cast<DiscordKit::opcodes::Gateway>(json.value("op", -1));
		if (handlers.contains(opcode)) {
			return handlers[opcode];
		}
		return std::nullopt;
	};

	template<typename Func> void register_handler_(const DiscordKit::opcodes::Gateway opcode, Func &&func)
	{
		handlers[opcode] = std::forward<Func>(func);
	};

	static std::unordered_map<DiscordKit::opcodes::Gateway, std::function<void(const nlohmann::json &)>> handlers;
	WSClient &parent;
};
