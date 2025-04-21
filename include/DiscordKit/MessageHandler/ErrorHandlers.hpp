//
// Created by Nikolai Käck on 2024-12-31.
//

#include "Event.hpp"

/** @brief Categorisation namespace for any logic regarding event handlers and callbacks
 *
 */
namespace DiscordKit::Events::Handlers
{
	/** @brief Handler class for managing error and close codes from the Discord Gateway
	 *
	 */
	class ErrorHandler
	{
	public:
		static bool onInvalidSession(const Event &event);
		static bool onUnknownError(const Event &event);
		static bool onUnknownOpcode(const Event &event);
		static bool onPayloadInvalid(const Event &event);
		static bool onAuthenticationFail(const Event &event);
		static bool onAuthenticationInvalid(const Event &event);
		static bool onAuthenticationDuplicate(const Event &event);
		static bool onInvalidSequence(const Event &event);
		static bool onRateLimit(const Event &event);
		static bool onSessionTimeout(const Event &event);
		static bool onInvalidShard(const Event &event);
		static bool onShardRequired(const Event &event);
		static bool onInvalidVersion(const Event &event);
		static bool onInvalidIntent(const Event &event);
		static bool onDisallowedIntent(const Event &event);
	};

}