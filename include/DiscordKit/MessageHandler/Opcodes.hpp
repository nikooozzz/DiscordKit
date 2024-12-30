//
// Created by Nikolai Käck on 2024-12-01.
//

#pragma once

namespace DiscordKit
{
	enum Opcode : int
	{
		DISPATCH		   = 0, // An event was dispatched. Type: Recieve
		HEARTBEAT		   = 1, // Fired periodically by the client to keep the connection alive. Type: Recieve & Send
		IDENTIFY		   = 2, // Starts a new session during the initial handshake. Type: Send
		PRESENCE_UPDATE	   = 3, // Update the client's presence. Type: Send
		VOICE_STATE_UPDATE = 4, // Used to join/leave or move between voice channels. Type: Send
		RESUME			   = 6, // Resume a previous session that was disconnected. Type: Send
		RECONNECT		   = 7, // Attempt to reconnect and resume immediately. Type: Recieve
		REQUEST_GUILD_MEMBERS = 8,	// Request information about offline guild members in a large guild.
		INVALID_SESSION		  = 9,	// The session has been invalidated. Reconnect and identify/resume accordingly.
		HELLO				  = 10, // Sent immediately after connecting, contains the heartbeat_interval to use.
		HEARTBEAT_ACK = 11, // Sent in response to receiving a heartbeat to acknowledge that it has been received.
		REQUEST_SOUNDBOARD_SOUNDS = 31, // Request information about soundboard sounds in a set of guilds.

		UNKNOWN_ERROR				 = 4000,
		UNKNOWN_OPCODE				 = 4001,
		PAYLOAD_INVALID				 = 4002,
		AUTHENTICATION_INVALID		 = 4003,
		AUTHENTICATION_FAIL			 = 4004,
		AUTHENTICATION_ALREADY_DONE = 4005,
		INVALID_SEQ					 = 4007,
		RATE_LIMIT					 = 4008,
		SESSION_TIMEOUT				 = 4009,
		SHARD_INVALID				 = 4010,
		SHARD_REQUIRED				 = 4011,
		INVALID_VERSION				 = 4012,
		INTENT_INVALID				 = 4013,
		INTENT_DISALLOWED			 = 4014
	};

}