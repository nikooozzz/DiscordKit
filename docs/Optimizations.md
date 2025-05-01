# Discordium Optimizations

This document details the performance optimizations implemented in the Discordium library. Each section describes a specific optimization, its problem, solution, and examples.

## 1. Snowflake ID Optimization

### Problem
Discord uses string-based IDs (snowflakes) which are inefficient for:
- Memory usage (variable length strings vs fixed size integers)
- Comparisons (string comparison vs integer comparison)
- Storage (string storage vs integer storage)
- Hashing (string hashing vs integer hashing)

### Solution
Convert string-based IDs to 64-bit integers internally while maintaining string compatibility for API communication.

### Implementation
```cpp
struct Snowflake {
    uint64_t id;
    Timestamp createdAt;

    // Perfect forwarding constructor for string inputs
    template<typename T>
    Snowflake(T&& id_str) : id(std::stoull(std::forward<T>(id_str))), 
                           createdAt(extractTimestamp(id)) {}

    // Integer constructor for direct ID assignment
    Snowflake(uint64_t id_val) : id(id_val), 
                                createdAt(extractTimestamp(id_val)) {}

    // Move semantics for efficient object transfer
    Snowflake(Snowflake&& other) noexcept 
        : id(other.id), createdAt(std::move(other.createdAt)) {}

    // Comparison operators for efficient sorting and searching
    bool operator==(const Snowflake& other) const { return id == other.id; }
    bool operator<(const Snowflake& other) const { return id < other.id; }
    // ... other comparison operators

    // Hash function for use in unordered containers
    struct Hash {
        size_t operator()(const Snowflake& sf) const {
            return std::hash<uint64_t>{}(sf.id);
        }
    };
};
```

### Benefits
- Reduced memory usage (8 bytes vs variable string length)
- O(1) comparisons instead of O(n) string comparisons
- Efficient hashing for use in containers
- Maintained API compatibility through conversion operators
- Better cache utilization due to fixed size

## 2. Vector Capacity Optimization

### Problem
Dynamic resizing of vectors causes:
- Multiple memory allocations
- Memory fragmentation
- Poor cache locality
- Unnecessary copying of elements

### Solution
Pre-allocate vector capacities based on typical usage patterns and reserve space when parsing JSON arrays.

### Implementation
```cpp
struct Message {
    std::vector<User> mentionedUsers;
    std::vector<Snowflake> roleMentions;
    std::vector<Attachment> attachments;
    std::vector<Embed> embeds;

    Message() {
        // Pre-allocate based on typical usage
        mentionedUsers.reserve(5);
        roleMentions.reserve(3);
        attachments.reserve(2);
        embeds.reserve(1);
    }

    static Message fromJson(const nlohmann::json& j) {
        Message m;
        // Reserve based on actual array size
        if (j.contains("mentions") && j["mentions"].is_array()) {
            const auto& mentions = j["mentions"];
            m.mentionedUsers.reserve(mentions.size());
            // ... populate vector
        }
    }
};
```

### Benefits
- Reduced number of memory allocations
- Better memory locality
- Improved cache utilization
- Reduced memory fragmentation
- More predictable performance

## 3. String View Optimization

### Problem
String parameters in functions cause:
- Unnecessary string copying
- Extra memory allocations
- Overhead in temporary string creation

### Solution
Use `std::string_view` for read-only string parameters to avoid copying.

### Implementation
```cpp
struct User {
    static User fromJson(std::string_view json_str) {
        auto j = nlohmann::json::parse(json_str);
        return fromJson(j);
    }
};
```

### Benefits
- Zero-copy string access
- No memory allocation overhead
- Efficient string parameter passing
- Reduced memory usage
- Better performance for temporary strings

## 4. String Capacity Optimization

### Problem
Dynamic string resizing causes:
- Multiple memory allocations
- Memory fragmentation
- Poor cache locality
- Unnecessary copying

### Solution
Pre-allocate string capacities based on typical usage patterns.

### Implementation
```cpp
struct Channel {
    std::string name;
    std::string topic;

    Channel() {
        name.reserve(32);    // Typical channel name length
        topic.reserve(1024); // Typical topic length
    }
};
```

### Benefits
- Reduced number of string reallocations
- Better memory locality
- Improved cache utilization
- Reduced memory fragmentation
- More predictable performance

## Future Optimizations

The following optimizations are planned but not yet implemented:

1. Memory Pool
2. String Interning
3. Compile-time Optimizations
4. Cache-friendly Data Structures
5. Lazy Loading
6. Batch Processing
7. Thread Safety
8. Error Handling

Each of these will be documented in detail as they are implemented. 