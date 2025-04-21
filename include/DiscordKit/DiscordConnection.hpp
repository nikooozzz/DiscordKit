//
// Created by Nikolai Käck on 2024-11-17.
//

#pragma once

#include <string>
#include "DiscordKit/Commands/BasicModels.hpp"
#include "DiscordKit/Intents.hpp"
#include "WSClient.hpp"

namespace DiscordKit
{
	/** @brief Main API abstraction for an average user.
	 *
	 * Handles a "DiscordConnection" object, allowing the library user to run a bot and add commands to it.
	 */
	class DiscordConnection
	{
	public:
		DiscordConnection(const Intents &intents, const std::string &token) : intents_(intents), ws_(token) {};

		void run()
		{
			ws_.Connect();
		};

		void SlashCommand(const std::string &name,
						  const std::string &description,
						  const std::function<void()> &handler)
		{
			ws_.RegisterCommand(Commands::BasicCommand(Commands::AppCommandType::SlashCommand, name, description, handler));
		};

		void UserCommand(const std::string &name,
						  const std::string &description,
						  const std::function<void()> &handler)
		{
			ws_.RegisterCommand(Commands::BasicCommand(Commands::AppCommandType::UserCommand, name, description, handler));
		}

		void MessageCommand(const std::string &name,
						  const std::string &description,
						  const std::function<void()> &handler)
		{
			ws_.RegisterCommand(Commands::BasicCommand(Commands::AppCommandType::MessageCommand, name, description, handler));
		}

		void ActivityCommand(const std::string &name,
						  const std::string &description,
						  const std::function<void()> &handler)
		{
			ws_.RegisterCommand(Commands::BasicCommand(Commands::AppCommandType::ActivityCommand, name, description, handler));
		}


	private:
		Intents intents_;
		WSClient ws_;
	};
} // namespace DiscordKit
