//
// Created by Nikolai Käck on 2024-12-31.
//

#pragma once

namespace DiscordKit::Commands
{

	enum AppCommandType
	{
		SlashCommand,
		UserCommand,
		MessageCommand,
		ActivityCommand
	};

	class BasicCommand
	{
	public:
		BasicCommand(const AppCommandType &type,
					 std::string name,
					 std::string description,
					 std::function<void()> callback) : type(type)
		{
			switch (type) {
				case SlashCommand: return SlashCommand(name, description, callback);
				case MessageCommand: return MessageCommand(name, description, callback);
				case ActivityCommand: return ActivityCommand(name, description, callback);
				case UserCommand: return UserCommand(name, description, callback);
			}
		}

		const AppCommandType type;
		std::string name;
		std::string description;
		std::function<void()> callback;
	};

}