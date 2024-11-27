//
// Created by Nikolai Käck on 2024-11-15.
//

#pragma once

#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace DiscordKit::con {

/**
* @brief This class handles a WebSocket connection
*
* It contains core methods for handling the websocket connection and adding callbacks to errors, connection calls and message handling
*/
class WSClient {
public:
	explicit WSClient(const std::string* token) : token_(*token) {
		this->setGatewayURL_(token_);
	};

	void Connect();
	void Disconnect();
	void Reconnect();
	bool IsConnected();

	void SendMessage();

	void SetOnMessage();
	void SetOnConnect();
	void SetOnDisconnect();
	void SetOnError();

private:
	void OnHandshakeComplete_();
	void HandleError_();
	void setGatewayURL_(std::string& token);

	boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws_con_;
	boost::asio::io_context ioc_{};
	boost::asio::ip::tcp::resolver resolver_{ioc_};

	std::string token_;
	std::string gateway_url_;
	std::string ip_;
};


}
