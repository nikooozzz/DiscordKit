//
// Created by Nikolai Käck on 2024-11-17.
//

#pragma once

#include <string>
#include "Intents.hpp"
#include "WSClient.hpp"

namespace DiscordKit::con {

class DiscordConnection {
	utils::Intents intents;

	DiscordConnection( const utils::Intents& intents ) : intents( intents ) {};

	void run( const std::string& token ) {
		WSClient ws{token};
		ws.connect();
	};


};


}