add_executable(game)

target_sources(game PRIVATE
    src/main.c
    # src/game.c
)

target_include_directories(game
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(game
    PRIVATE engine
)
