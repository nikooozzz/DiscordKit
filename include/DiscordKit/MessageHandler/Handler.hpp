//
// Created by Nikolai Käck on 2024-12-28.
//

#pragma once
#include "Event.hpp"

#include "DiscordKit/Commands/BasicModels.hpp"

namespace DiscordKit::Events::Handlers
{
	/** @brief Mapping tool for Dispatch Events (Opcode 0) and their callbacks
	 *
	 */
	class DispatchEventHandler
	{
	public:
		bool handle(const Event &event) {

		};

		void addHandler(const Commands::BasicCommand &command)
		{
			switch (command.type) {
				case Commands::SlashCommand: slash_command_handlers[command.name] = command.callback; break;
				case Commands::UserCommand: user_command_handlers[command.name] = command.callback; break;
				case Commands::MessageCommand: message_command_handlers[command.name] = command.callback; break;
				case Commands::ActivityCommand: activity_command_handlers[command.name] = command.callback; break;
			}
		};

	private:
		std::unordered_map<std::string, std::function<void()>> slash_command_handlers;
		std::unordered_map<std::string, std::function<void()>> user_command_handlers;
		std::unordered_map<std::string, std::function<void()>> message_command_handlers;
		std::unordered_map<std::string, std::function<void()>> activity_command_handlers;
	};

}; // namespace DiscordKit::Events::Handlers
