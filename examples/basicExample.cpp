#include "DiscordKit/conn/WSClient.hpp"
#include <boost/asio.hpp>

int main() {

	boost::asio::io_context ioc;
	DiscordKit::Connection::WSClient cl{ioc};

}