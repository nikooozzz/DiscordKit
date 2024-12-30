//
// Created by Nikolai Käck on 2024-11-15.
//

/**
 * @file
 * Application-level setup
 */

#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast/websocket.hpp>

#include <iostream>
#include <nlohmann/json.hpp>
#include <thread>
#include <utility>

#include "DiscordKit/MessageHandler.hpp"
#include "DiscordKit/MessageHandler/Dispatcher.hpp"
#include "DiscordKit/MessageHandler/Opcodes.hpp"

namespace beast		= boost::beast;
namespace asio		= boost::asio;
using tcp			= asio::ip::tcp;
namespace websocket = beast::websocket;

/**
 * @brief This class handles a WebSocket connection
 *
 * It contains core methods for handling the websocket connection and adding callbacks to errors, connection calls and
 * message handling
 */
namespace DiscordKit
{
	class WSClient
	{
	public:
		explicit WSClient(std::string token) :
			token_(std::move(token)), gateway_url_(fetchGatewayURL_()), ioc_(),
			ssl_ctx_(asio::ssl::context::tlsv12_client), resolver_(ioc_), ws_(ioc_, ssl_ctx_)
		{
			ssl_ctx_.set_default_verify_paths();
		};

		/** @brief Connects to the WebSocket server asynchronously. */
		void Connect(bool isReconnect = false)
		{
			resolver_.async_resolve(
					gateway_url_, "443",
					[this](const boost::system::error_code &resec, const tcp::resolver::results_type &results)
					{
						if (HandleError_(resec, "Resolve")) return;

						asio::async_connect(ws_.next_layer().next_layer().socket(), results,
											[this](const boost::system::error_code &conec, const tcp::endpoint &)
											{
												if (HandleError_(conec, "Connect")) return;

												ws_.next_layer().async_handshake(
														asio::ssl::stream_base::client,
														[this](const boost::system::error_code &sslec)
														{
															if (HandleError_(sslec, "SSL Handshake")) return;

															ws_.async_handshake(
																	gateway_url_, "/?v=10&encoding=json",
																	[this](const boost::system::error_code &wsec)
																	{
																		if (HandleError_(wsec, "Websocket Handshake"))
																			return;
																		SendIdentity();
																	});
														});
											});
					});

			std::thread([this] { ioc_.run(); }).detach();
		}

		void SendIdentity()
		{
			std::string identity = R"({
				"op": 2,
				"d": {
					"token": ")" +
					this->token_ + R"(",
					"intents": 513,
					"properties": {
						"$os": "linux",
	                    "$browser": "boost",
	                    "$device": "boost"
	                }
	            }
				})";

			ws_.write(asio::buffer(identity));
		}

		void ReadLoop()
		{
			ws_.async_read(buffer_,
						   [this](const boost::system::error_code &ec, const std::size_t bytes)
						   {
							   if (ec) {
								   std::cerr << ec.message() << std::endl;
								   Reconnect();
								   return;
							   }

							   const nlohmann::json &msg =
									   nlohmann::json::parse(beast::buffers_to_string(buffer_.data()));
							   buffer_.consume(bytes);

							   HandleMessage_(msg);

							   ReadLoop();
						   });
		}

		/** @brief Disconnects from the WebSocket server. */
		void Disconnect()
		{
			if (ws_.is_open()) {
				ws_.async_close(websocket::close_code::normal,
								[this](const boost::system::error_code &ec) { HandleError_(ec, "Disconnect"); });
			}
		};

		/** @brief Reconnects to the WebSocket server. */
		void Reconnect()
		{
			Connect(true);
		};

		/** @brief Checks if the WebSocket connection is active.
		 *  @return `true` if connected, `false` otherwise.
		 */
		bool IsConnected() const
		{
			return ws_.is_open();
		};

		/** @brief Sends a message through the WebSocket connection. */
		void SendMessage();

		/** @brief Sets the callback function for connection events. */
		void SetOnConnect();

		/** @brief Sets the callback function for disconnection events. */
		void SetOnDisconnect();

		/** @brief Sets the callback function for error events. */
		void SetOnError();


	private:
		/** @brief Callback function for incoming websocket messages. */
		void HandleMessage_(const nlohmann::json &msg)
		{
			dispatcher_.handle(DiscordKit::Events::Event(msg));
		};

		/** @brief Handles errors during WebSocket communication. */
		bool HandleError_(const boost::system::error_code &ec, const std::string &stage)
		{
			if (ec) {
				std::cerr << stage << " error: " << ec.message() << std::endl;
				Reconnect();
				return true;
			}
			return false;
		};

		/** @brief Gets a gateway URL endpoint from the discord api */
		std::string fetchGatewayURL_()
		{
			try {
				asio::ssl::context ssl_ctx(asio::ssl::context::sslv23_client);

				tcp::resolver resolver{ioc_};
				auto const endpoint = resolver.resolve("discord.com", "https");

				beast::tcp_stream stream{ioc_};
				stream.connect(endpoint);

				beast::ssl_stream<beast::tcp_stream> ssl_stream(std::move(stream), ssl_ctx);
				ssl_stream.handshake(asio::ssl::stream_base::client);

				beast::http::request<beast::http::string_body> req{beast::http::verb::get, "/api/v10/gateway", 11};
				req.set(beast::http::field::host, "discord.com");
				req.set(beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

				beast::http::write(ssl_stream, req);

				beast::flat_buffer buffer;
				beast::http::response<beast::http::string_body> res;

				beast::http::read(ssl_stream, buffer, res);
				std::cout << res << std::endl;

				ssl_stream.shutdown();

				return nlohmann::json::parse(res.body())["url"];
			}
			catch (const std::exception &e) {
				std::cerr << "Error: " << e.what() << std::endl;
			}

			return nullptr;
		};

		/** @brief Sets the gateway URL member */
		void setGatewayURL_()
		{
			this->gateway_url_ = fetchGatewayURL_();
		};

		std::string token_;
		std::string gateway_url_;

		asio::io_context ioc_;
		asio::ssl::context ssl_ctx_;
		tcp::resolver resolver_;
		websocket::stream<beast::ssl_stream<beast::tcp_stream>> ws_;

		beast::flat_buffer buffer_;

		Events::Dispatcher dispatcher_;
	};
}