//
// Created by Nikolai Käck on 2024-12-28.
//

#pragma once
#include "Event.hpp"

namespace DiscordKit::Events::Handlers
{

	class GeneralHandler
	{
	public:
		GeneralHandler();

		int handles_op;
	};

	class DispatchEventHandler : public GeneralHandler
	{
	public:
		DispatchEventHandler();

		int handles_op = 0;
	};

	class AppCommandHandler : public DispatchEventHandler
	{
	public:
		AppCommandHandler();
	};

	class SlashCommandHandler : public AppCommandHandler
	{
	public:
		std::unordered_map<std::string, std::function<void()>> handlers;
	};

}