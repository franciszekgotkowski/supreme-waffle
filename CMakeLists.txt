cmake_minimum_required(VERSION 3.10)

project(MyGame C)

set(CMAKE_CONFIGURATION_TYPES
    Debug
    Release
    Benchmark
    DebugBenchmark
    CACHE STRING "Available build types"
)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type")
endif()

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(ENGINE_ENABLE_ASSERTS "Enable engine asserts" ON)
option(GAME_ENABLE_ASSERTS "Enable engine asserts" ON)

add_subdirectory(engine)
add_subdirectory(game)
