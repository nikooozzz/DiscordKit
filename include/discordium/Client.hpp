#include <string>
#include <functional>


class Client {
    public:
        Client();
        ~Client();

        // == Connection Management ==

        void connect(const std::string& token);
        void disconnect();

        // == Channel Management ==
        void createChannel(const std::string& name);
        void deleteChannel(const std::string& channelId);
        void getChannel(const std::string& channelId);
        
        // == Message Management ==
        void sendMessage(const std::string& channelId, const std::string& message);
        void deleteMessage(const std::string& channelId, const std::string& messageId);
        void editMessage(const std::string& channelId, const std::string& messageId, const std::string& newContent);
        void getMessage(const std::string& channelId, const std::string& messageId);

        // == User Management ==
        void getUser(const std::string& userId);
        void getCurrentUser();

        // == Event Handling ==
        void onReady(std::function<void()> callback);
        void onError(std::function<void(const std::string&)> callback);

        void onChannelCreate(std::function<void(const std::string&)> callback);
        void onChannelDelete(std::function<void(const std::string&)> callback);
        void onChannelEdit(std::function<void(const std::string&)> callback);

        void onMessage(std::function<void(const std::string&)> callback);
        void onMessageDelete(std::function<void(const std::string&)> callback);
        void onMessageEdit(std::function<void(const std::string&)> callback);

        void onMemberJoin(std::function<void(const std::string&)> callback);
        void onMemberLeave(std::function<void(const std::string&)> callback);
        void onMemberUpdate(std::function<void(const std::string&)> callback);
        void onPresenceUpdate(std::function<void(const std::string&)> callback);

        void onReaction(std::function<void(const std::string&)> callback);
        void onReactionRemove(std::function<void(const std::string&)> callback);
        void onReactionClear(std::function<void(const std::string&)> callback);

        void onRoleCreate(std::function<void(const std::string&)> callback);
        void onRoleDelete(std::function<void(const std::string&)> callback);
        void onRoleUpdate(std::function<void(const std::string&)> callback);

        void onVoiceStateUpdate(std::function<void(const std::string&)> callback);

        void onGuildJoin(std::function<void(const std::string&)> callback);
        void onGuildLeave(std::function<void(const std::string&)> callback);
        void onGuildUpdate(std::function<void(const std::string&)> callback);

        void onInviteCreate(std::function<void(const std::string&)> callback);
        void onInviteDelete(std::function<void(const std::string&)> callback);

        void onInteraction(std::function<void(const std::string&)> callback);
        void onApplicationCommand(std::function<void(const std::string&)> callback);

    private:
        std::string token;
        std::function<void(const std::string&)> messageCallback;

        void handleMessageReceived(const std::string& message);
        void handleError(const std::string& error);
};