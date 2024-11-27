//
// Created by Nikolai Käck on 2024-11-17.
//

#pragma once

#include <bitset>

enum class Intents : uint64_t {
		GUILD_MESSAGES = 1 << 0,       // Guild messages
		DIRECT_MESSAGES = 1 << 1,     // Direct messages
		GUILD_MEMBERS = 1 << 2,       // Guild member events
		GUILD_VOICE_STATES = 1 << 3,  // Voice state updates
		GUILD_EMOJIS = 1 << 4,        // Guild emojis updates
		GUILD_WEBHOOKS = 1 << 5,      // Guild webhook updates
		GUILD_INVITES = 1 << 6,       // Guild invite updates
		MESSAGE_REACTIONS = 1 << 7,   // Message reaction events
		GUILD_PRESENCES = 1 << 8,     // Guild presences (requires privileged intent)
		GUILD_BANS = 1 << 9,          // Guild ban events
		ALL = 0xFFFFFFFFFFFFFFFF
	};

inline Intents operator|(Intents lhs, Intents rhs) {
		return static_cast<Intents>(
			static_cast<uint64_t>(lhs) | static_cast<uint64_t>(rhs));
	}

// Check for specific intents using bitwise AND
inline bool operator&(Intents lhs, Intents rhs) {
		return static_cast<uint64_t>(lhs) & static_cast<uint64_t>(rhs);
}

// Allow combining intents into a single bitmask
inline Intents& operator|=(Intents& lhs, Intents rhs) {
		lhs = lhs | rhs;
		return lhs;
}

