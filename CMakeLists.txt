cmake_minimum_required(VERSION 3.20)
project(discordium VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(DISCORDIUM_BUILD_EXAMPLES "Build examples" ON)
option(DISCORDIUM_BUILD_TESTS "Build tests" ON)

add_library(discordium STATIC)

target_include_directories(discordium PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

file(GLOB_RECURSE DISCORDIUM_SOURCES CONFIGURE_DEPENDS 
    src/*.cpp
)
file(GLOB_RECURSE DISCORDIUM_HEADERS CONFIGURE_DEPENDS 
    include/discordium/*.hpp
)
target_sources(discordium PRIVATE ${DISCORDIUM_SOURCES})

add_library(discordium::discordium ALIAS discordium)

if (DISCORDIUM_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if (DISCORDIUM_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

include(GNUInstallDirs)

install(TARGETS discordium
    EXPORT discordiumTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT discordiumTargets
    FILE discordiumConfig.cmake
    NAMESPACE discordium::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/discordium
)

find_package(nlohmann_json REQUIRED)
target_link_libraries(discordium PUBLIC nlohmann_json::nlohmann_json)

if(MSVC)
    target_compile_options(discordium PRIVATE /W4)
else()
    target_compile_options(discordium PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_compile_definitions(discordium PUBLIC
    DISCORDIUM_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    DISCORDIUM_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    DISCORDIUM_VERSION_PATCH=${PROJECT_VERSION_PATCH}
)
