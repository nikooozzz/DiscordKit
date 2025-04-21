include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

add_executable(discordium-tests test_main.cpp)
target_link_libraries(discordium-tests PRIVATE discordium Catch2::Catch2WithMain)
target_compile_features(discordium-tests PRIVATE cxx_std_20)

include(CTest)
include(Catch)
catch_discover_tests(discordium-tests)
