add_executable(tests)

target_sources(tests PRIVATE

)

target_include_directories(tests PRIVATE
	${CMAKE_HOME_DIRECTORY}/engine/headers
	${CMAKE_CURRENT_SOURCE_DIR}/headers
)

target_link_directories(tests PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/libs/dynamic
	${CMAKE_CURRENT_SOURCE_DIR}/libs/static
	${CMAKE_HOME_DIRECTORY}/engine/libs/static
)


target_link_libraries(tests
	PRIVATE engine
)

