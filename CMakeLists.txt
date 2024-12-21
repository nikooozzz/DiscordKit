cmake_minimum_required(VERSION 3.15)
project(DiscordKit VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.86 REQUIRED COMPONENTS system)

add_library(DiscordKit INTERFACE)

target_include_directories(DiscordKit INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(DiscordKit INTERFACE Boost::system)

add_executable(basicExample examples/basicExample.cpp)
target_link_libraries(basicExample PRIVATE DiscordKit)