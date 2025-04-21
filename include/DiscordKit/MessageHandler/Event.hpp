//
// Created by Nikolai Käck on 2024-12-28.
//

#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace DiscordKit::Events
{
	/** @brief Model class for the discord gateway event payload structure
	 *
	 */
	class Event
	{
	public:
		explicit Event(const nlohmann::json &json) :
			opcode(json["op"]), data(json["d"]), seq(json["s"]), name(json["t"]) {};

		int opcode;
		nlohmann::json data;
		int seq = 0;
		std::string name;
	};

}