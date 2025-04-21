//
// Created by Nikolai Käck on 2024-12-31.
//

#pragma once
#include <functional>
#include <string>

#include "DiscordKit/Commands/BasicModels.hpp"

namespace DiscordKit::Commands
{

	class SlashCommand : public BasicCommand
	{
	public:
		const AppCommandType type = AppCommandType::SlashCommand;
	};

} // namespace DiscordKit::Commands
