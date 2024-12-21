#include <list>

#include <string>
#include "DiscordKit/DiscordKit.hpp"

int main() {
	std::string token;
	DiscordConnection bot{Intents::ALL};

	bot.run(token);
}