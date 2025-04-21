//
// Created by Nikolai Käck on 2024-12-28.
//

#pragma once
#include <functional>
#include <iostream>

#include "ErrorHandlers.hpp"
#include "Event.hpp"
#include "Handler.hpp"
#include "Opcodes.hpp"

using OP = DiscordKit::Opcode;

/** @brief Categorisation namespace for any logic regarding incoming events in the Discord Gateway
 *
 */
namespace DiscordKit::Events
{
	/** @brief Handler class for mapping and directing incoming events to respective callbacks
	 *
	 */
	class Dispatcher
	{
	public:
		Dispatcher()
		{
			handler_map_[OP::DISPATCH]		  = dispatch_event_handler_.handle;
			handler_map_[OP::INVALID_SESSION] = Handlers::ErrorHandler::onInvalidSession;
			handler_map_[OP::HEARTBEAT];
			handler_map_[OP::RECONNECT];
			handler_map_[OP::HELLO];
			handler_map_[OP::HEARTBEAT_ACK];

			close_handler_map_[OP::UNKNOWN_ERROR]				= Handlers::ErrorHandler::onUnknownError;
			close_handler_map_[OP::UNKNOWN_OPCODE]				= Handlers::ErrorHandler::onUnknownOpcode;
			close_handler_map_[OP::PAYLOAD_INVALID]				= Handlers::ErrorHandler::onPayloadInvalid;
			close_handler_map_[OP::AUTHENTICATION_FAIL]			= Handlers::ErrorHandler::onAuthenticationFail;
			close_handler_map_[OP::AUTHENTICATION_INVALID]		= Handlers::ErrorHandler::onAuthenticationInvalid;
			close_handler_map_[OP::AUTHENTICATION_ALREADY_DONE] = Handlers::ErrorHandler::onAuthenticationDuplicate;
			close_handler_map_[OP::INVALID_SEQ]					= Handlers::ErrorHandler::onInvalidSequence;
			close_handler_map_[OP::RATE_LIMIT]					= Handlers::ErrorHandler::onRateLimit;
			close_handler_map_[OP::SESSION_TIMEOUT]				= Handlers::ErrorHandler::onSessionTimeout;
			close_handler_map_[OP::SHARD_INVALID]				= Handlers::ErrorHandler::onInvalidShard;
			close_handler_map_[OP::SHARD_REQUIRED]				= Handlers::ErrorHandler::onShardRequired;
			close_handler_map_[OP::INVALID_VERSION]				= Handlers::ErrorHandler::onInvalidVersion;
			close_handler_map_[OP::INTENT_INVALID]				= Handlers::ErrorHandler::onInvalidIntent;
			close_handler_map_[OP::INTENT_DISALLOWED]			= Handlers::ErrorHandler::onDisallowedIntent;
		};

		bool handle(const Event &event)
		{
			if (event.opcode <= 31) {
				return runNormalHandler(event);
			} else if (event.opcode >= 4000 && event.opcode <= 4014) {
				return runCloseHandler(event);
			}
			return false;
		};

		bool runNormalHandler(const Event &event)
		{
			if (const auto handler = handler_map_.find(event.opcode); handler != handler_map_.end()) {
				return handler->second(event);
			}

			std::cerr << "Unknown opcode " << event.opcode << std::endl;
			return false;
		}

		bool runCloseHandler(const Event &event)
		{
			if (const auto handler = close_handler_map_.find(event.opcode); handler != close_handler_map_.end()) {
				return handler->second(event);
			}

			std::cerr << "Unknown opcode " << event.opcode << std::endl;
			return false;
		}

		void RegisterCommand(const Commands::BasicCommand &command)
		{
			dispatch_event_handler_.addHandler(command);
		}

	private:
		std::unordered_map<int, std::function<bool(const Event &)>> handler_map_;
		std::unordered_map<int, std::function<bool(const Event &)>> close_handler_map_;
		Handlers::DispatchEventHandler dispatch_event_handler_;
	};
}