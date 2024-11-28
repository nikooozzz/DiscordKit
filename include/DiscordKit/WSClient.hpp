//
// Created by Nikolai Käck on 2024-11-15.
//

/**
* @file
* Application-level setup
*/

#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <iostream>
#include <nlohmann/json.hpp>


/**
* @brief This class handles a WebSocket connection
*
* It contains core methods for handling the websocket connection and adding callbacks to errors, connection calls and message handling
*/
class WSClient {
public:
	explicit WSClient(const std::string* token) : token_(*token) {
		this->setGatewayURL_();
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
	void setGatewayURL_() {
		try {
		boost::asio::io_context ioc;
		boost::asio::ssl::context ssl_ctx(boost::asio::ssl::context::sslv23_client);

		boost::asio::ip::tcp::resolver resolver{ioc};
		auto const endpoint = resolver.resolve("discord.com", "https")

		boost::beast::tcp_stream stream{ioc};
		stream.connect(endpoint);

		boost::beast::ssl_stream<boost::beast::tcp_stream> ssl_stream(std::move(stream), ssl_ctx);
		ssl_stream.handshake(boost::asio::ssl::stream_base::client);

		boost::beast::http::request<boost::beast::http::string_body> req{
    	boost::beast::http::verb::get, "/api/v10/gateway", 11};
		req.set(boost::beast::http::field::host, "discord.com");
		req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

		boost::beast::http::write(ssl_stream, req);

		boost::beast::flat_buffer buffer;
		boost::beast::http::response<boost::beast::http::string_body> res;

		boost::beast::http::read(ssl_stream, buffer, res);
		std::cout << res << std::endl;

		ssl_stream.shutdown();

		this->gateway_url_ = json.parse(res)["url"];
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}

		return 0;
	};

	std::string token_;
	std::string gateway_url_;
	std::string ip_;
};



