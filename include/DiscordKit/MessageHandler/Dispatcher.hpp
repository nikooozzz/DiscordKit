//
// Created by Nikolai Käck on 2024-12-28.
//

#pragma once
#include <functional>
#include <nlohmann/json.hpp>

#include "Event.hpp"
#include "Handler.hpp"
#include "Opcodes.hpp"

using OP		  = DiscordKit::Opcode;
using HandlerFunc = std::function<void(const DiscordKit::Event &)>;

void dispatch(const DiscordKit::Event &event);

namespace DiscordKit::Events
{
	class Dispatcher
	{
	public:
		Dispatcher()
		{
			handlerMap[OP::DISPATCH] = dispatch; // Example for future reference
		};

		void handle(const DiscordKit::Event &event)
		{
			if (const auto handler = handlerMap.find(event.opcode); handler != handlerMap.end()) {
				handler->second(event);
			}
			else {
				std::cerr << "Unknown opcode " << event.opcode << std::endl;
			}
		};

	private:
		std::unordered_map<int, HandlerFunc> handlerMap;
	};
}