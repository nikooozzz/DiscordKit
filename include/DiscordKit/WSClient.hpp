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

	/** @brief Connects to the WebSocket server. */
	void Connect();

	/** @brief Disconnects from the WebSocket server. */
	void Disconnect();

	/** @brief Reconnects to the WebSocket server. */
	void Reconnect();

	/** @brief Checks if the WebSocket connection is active.
     *  @return `true` if connected, `false` otherwise.
     */
	bool IsConnected();

	/** @brief Sends a message through the WebSocket connection. */
	void SendMessage();

	/** @brief Sets the callback function for message reception. */
	void SetOnMessage();

	/** @brief Sets the callback function for connection events. */
	void SetOnConnect();

	/** @brief Sets the callback function for disconnection events. */
	void SetOnDisconnect();

	/** @brief Sets the callback function for error events. */
	void SetOnError();

private:
	/** @brief Handles the WebSocket handshake completion. */
	void OnHandshakeComplete_();

	/** @brief Handles errors during WebSocket communication. */
	void HandleError_();

	/** @brief Sets the gateway URL using the provided token */
	void setGatewayURL_(std::string& token);

	boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws_con_;
	boost::asio::io_context ioc_{};
	boost::asio::ip::tcp::resolver resolver_{ioc_};

	std::string token_;
	std::string gateway_url_;
	std::string ip_;
};


}
