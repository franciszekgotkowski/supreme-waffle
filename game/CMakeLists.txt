add_executable(game)

target_sources(game PRIVATE
		src/main.c
		src/game_loop.c
		src/input_functions.c
)

target_include_directories(game PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/headers

		${CMAKE_HOME_DIRECTORY}/engine/headers
		${CMAKE_HOME_DIRECTORY}/common/headers

#		ONLY FOR DEBUG PURPOSES
		${CMAKE_HOME_DIRECTORY}/platform/headers/export
		${CMAKE_HOME_DIRECTORY}/platform/headers/external
)

target_link_directories(game PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/libs/dynamic
		${CMAKE_CURRENT_SOURCE_DIR}/libs/static
		${CMAKE_HOME_DIRECTORY}/engine/libs/static

#		ONLY FOR DEBUG PURPOSES
		${CMAKE_HOME_DIRECTORY}/platform/libs/linux/static
		${CMAKE_HOME_DIRECTORY}/platform/libs/windows/static
)


target_link_libraries(game PRIVATE
		engine
		glfw3
		platform
		common
)

