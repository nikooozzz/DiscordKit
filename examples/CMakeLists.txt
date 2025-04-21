add_executable(example-client example_client.cpp)
target_link_libraries(example-client PRIVATE discordium)
target_compile_features(example-client PRIVATE cxx_std_20)