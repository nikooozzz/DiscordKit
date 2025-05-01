#pragma once

#include <string>
#include <functional>
#include <cstdint>

class Client {
    public:
        Client();
        ~Client();

        // == Connection Management ==

        void connect(const std::string& token);
        void disconnect();

        // == Channel Management ==
        void createChannel(const std::string& name);
        void deleteChannel(uint64_t channelId);
        void getChannel(uint64_t channelId);
        
        // == Message Management ==
        void sendMessage(uint64_t channelId, const std::string& message);
        void deleteMessage(uint64_t channelId, uint64_t messageId);
        void editMessage(uint64_t channelId, uint64_t messageId, const std::string& newContent);
        void getMessage(uint64_t channelId, uint64_t messageId);

        // == User Management ==
        void getUser(uint64_t userId);
        void getCurrentUser();

        // == Event Handling ==
        void onReady(std::function<void()> callback);
        void onError(std::function<void(const std::string&)> callback);

        void onChannelCreate(std::function<void(uint64_t)> callback);
        void onChannelDelete(std::function<void(uint64_t)> callback);
        void onChannelEdit(std::function<void(uint64_t)> callback);

        void onMessage(std::function<void(uint64_t)> callback);
        void onMessageDelete(std::function<void(uint64_t)> callback);
        void onMessageEdit(std::function<void(uint64_t)> callback);

        void onMemberJoin(std::function<void(uint64_t)> callback);
        void onMemberLeave(std::function<void(uint64_t)> callback);
        void onMemberUpdate(std::function<void(uint64_t)> callback);
        void onPresenceUpdate(std::function<void(uint64_t)> callback);

        void onReaction(std::function<void(uint64_t)> callback);
        void onReactionRemove(std::function<void(uint64_t)> callback);
        void onReactionClear(std::function<void(uint64_t)> callback);

        void onRoleCreate(std::function<void(uint64_t)> callback);
        void onRoleDelete(std::function<void(uint64_t)> callback);
        void onRoleUpdate(std::function<void(uint64_t)> callback);

        void onVoiceStateUpdate(std::function<void(uint64_t)> callback);

        void onGuildJoin(std::function<void(uint64_t)> callback);
        void onGuildLeave(std::function<void(uint64_t)> callback);
        void onGuildUpdate(std::function<void(uint64_t)> callback);

        void onInviteCreate(std::function<void(uint64_t)> callback);
        void onInviteDelete(std::function<void(uint64_t)> callback);

        void onInteraction(std::function<void(uint64_t)> callback);
        void onApplicationCommand(std::function<void(uint64_t)> callback);

    private:
        std::string token;
        std::function<void(const std::string&)> messageCallback;

        void handleMessageReceived(const std::string& message);
        void handleError(const std::string& error);
};