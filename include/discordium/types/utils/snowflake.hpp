#pragma once

#include <string>
#include <chrono>
#include "time.hpp"

struct Snowflake {
    uint64_t id;
    Timestamp createdAt;

    Snowflake() : id(0), createdAt(Timestamp()) {}

    template<typename T>
    Snowflake(T&& id_str) : id(std::stoull(std::forward<T>(id_str))), createdAt(extractTimestamp(id)) {}

    Snowflake(uint64_t id_val) : id(id_val), createdAt(extractTimestamp(id_val)) {}

    Snowflake(Snowflake&& other) noexcept : id(other.id), createdAt(std::move(other.createdAt)) {}

    Snowflake& operator=(Snowflake&& other) noexcept {
        if (this != &other) {
            id = other.id;
            createdAt = std::move(other.createdAt);
        }
        return *this;
    }

    Snowflake(const Snowflake& other) = default;
    Snowflake& operator=(const Snowflake& other) = default;

    operator std::string() const { return std::to_string(id); }
    operator uint64_t() const { return id; }

    bool operator==(const Snowflake& other) const { return id == other.id; }
    bool operator!=(const Snowflake& other) const { return id != other.id; }
    bool operator<(const Snowflake& other) const { return id < other.id; }
    bool operator>(const Snowflake& other) const { return id > other.id; }
    bool operator<=(const Snowflake& other) const { return id <= other.id; }
    bool operator>=(const Snowflake& other) const { return id >= other.id; }

    struct Hash {
        size_t operator()(const Snowflake& sf) const {
            return std::hash<uint64_t>{}(sf.id);
        }
    };

    Timestamp extractTimestamp(uint64_t snowflake_id) {
        uint64_t timestamp = snowflake_id >> 22; 
        uint64_t timestamp_ms = timestamp + 1420070400000; 
        std::chrono::milliseconds ms(timestamp_ms);
        std::chrono::system_clock::time_point tp(ms);
        return Timestamp(tp); 
    }
};