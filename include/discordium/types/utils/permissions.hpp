#pragma once

#include <iostream>

class Permissions {
public:
    enum Permission {
        SEND_MESSAGES         = 1 << 0,      // 1
        MANAGE_MESSAGES       = 1 << 1,      // 2
        BAN_MEMBERS           = 1 << 2,      // 4
        KICK_MEMBERS          = 1 << 3,      // 8
        MANAGE_ROLES          = 1 << 4,      // 16
        ADMINISTRATOR         = 1 << 5,      // 32
        READ_MESSAGES         = 1 << 6,      // 64
        SEND_TTS_MESSAGES     = 1 << 7,      // 128
        MANAGE_CHANNELS       = 1 << 8,      // 256
        MANAGE_GUILD          = 1 << 9,      // 512
        ADD_REACTIONS         = 1 << 10,     // 1024
        VIEW_AUDIT_LOGS       = 1 << 11,     // 2048
        PRIORITY_SPEAKER      = 1 << 12,     // 4096
        STREAM                = 1 << 13,     // 8192
        CONNECT               = 1 << 14,     // 16384
        SPEAK                 = 1 << 15,     // 32768
        MUTE_MEMBERS          = 1 << 16,     // 65536
        DEAFEN_MEMBERS        = 1 << 17,     // 131072
        MOVE_MEMBERS          = 1 << 18,     // 262144
        USE_VAD               = 1 << 19,     // 524288
        CHANGE_NICKNAME       = 1 << 20,     // 1048576
        MANAGE_NICKNAMES      = 1 << 21,     // 2097152
        MANAGE_EMOJIS         = 1 << 22,     // 4194304
        MANAGE_WEBHOOKS       = 1 << 23,     // 8388608
        USE_EXTERNAL_EMOJIS   = 1 << 24,     // 16777216
        VIEW_CHANNEL          = 1 << 25,     // 33554432
        READ_MESSAGE_HISTORY  = 1 << 26,     // 67108864
        INVITE_TO_SERVER      = 1 << 27      // 134217728
    };

private:
    int permissions;

public:
    Permissions(int permissions = 0) : permissions(permissions) {}

    bool hasPermission(Permission perm) const {
        return (permissions & perm) != 0;
    }

    void setPermission(Permission perm, bool value) {
        if (value) {
            permissions |= perm;
        } else {
            permissions &= ~perm;
        }
    }

    void printPermissions() const {
        std::cout << "Permissions: " << std::endl;
        if (hasPermission(SEND_MESSAGES)) std::cout << "- SEND_MESSAGES" << std::endl;
        if (hasPermission(MANAGE_MESSAGES)) std::cout << "- MANAGE_MESSAGES" << std::endl;
        if (hasPermission(BAN_MEMBERS)) std::cout << "- BAN_MEMBERS" << std::endl;
        if (hasPermission(KICK_MEMBERS)) std::cout << "- KICK_MEMBERS" << std::endl;
        if (hasPermission(MANAGE_ROLES)) std::cout << "- MANAGE_ROLES" << std::endl;
        if (hasPermission(ADMINISTRATOR)) std::cout << "- ADMINISTRATOR" << std::endl;
        if (hasPermission(READ_MESSAGES)) std::cout << "- READ_MESSAGES" << std::endl;
        if (hasPermission(SEND_TTS_MESSAGES)) std::cout << "- SEND_TTS_MESSAGES" << std::endl;
        if (hasPermission(MANAGE_CHANNELS)) std::cout << "- MANAGE_CHANNELS" << std::endl;
        if (hasPermission(MANAGE_GUILD)) std::cout << "- MANAGE_GUILD" << std::endl;
        if (hasPermission(ADD_REACTIONS)) std::cout << "- ADD_REACTIONS" << std::endl;
        if (hasPermission(VIEW_AUDIT_LOGS)) std::cout << "- VIEW_AUDIT_LOGS" << std::endl;
        if (hasPermission(PRIORITY_SPEAKER)) std::cout << "- PRIORITY_SPEAKER" << std::endl;
        if (hasPermission(STREAM)) std::cout << "- STREAM" << std::endl;
        if (hasPermission(CONNECT)) std::cout << "- CONNECT" << std::endl;
        if (hasPermission(SPEAK)) std::cout << "- SPEAK" << std::endl;
        if (hasPermission(MUTE_MEMBERS)) std::cout << "- MUTE_MEMBERS" << std::endl;
        if (hasPermission(DEAFEN_MEMBERS)) std::cout << "- DEAFEN_MEMBERS" << std::endl;
        if (hasPermission(MOVE_MEMBERS)) std::cout << "- MOVE_MEMBERS" << std::endl;
        if (hasPermission(USE_VAD)) std::cout << "- USE_VAD" << std::endl;
        if (hasPermission(CHANGE_NICKNAME)) std::cout << "- CHANGE_NICKNAME" << std::endl;
        if (hasPermission(MANAGE_NICKNAMES)) std::cout << "- MANAGE_NICKNAMES" << std::endl;
        if (hasPermission(MANAGE_EMOJIS)) std::cout << "- MANAGE_EMOJIS" << std::endl;
        if (hasPermission(MANAGE_WEBHOOKS)) std::cout << "- MANAGE_WEBHOOKS" << std::endl;
        if (hasPermission(USE_EXTERNAL_EMOJIS)) std::cout << "- USE_EXTERNAL_EMOJIS" << std::endl;
        if (hasPermission(VIEW_CHANNEL)) std::cout << "- VIEW_CHANNEL" << std::endl;
        if (hasPermission(READ_MESSAGE_HISTORY)) std::cout << "- READ_MESSAGE_HISTORY" << std::endl;
        if (hasPermission(INVITE_TO_SERVER)) std::cout << "- INVITE_TO_SERVER" << std::endl;
    }
};