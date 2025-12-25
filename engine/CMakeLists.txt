add_library(engine STATIC)

set(ENGINE_SOURCES
		src/loop.c
)

if(UNIX)
	list(APPEND
			ENGINE_SOURCES
			src/memory/memory_linux.c
	)
	target_link_directories(engine PUBLIC
			${CMAKE_CURRENT_SOURCE_DIR}/libs/linux/dynamic
			${CMAKE_CURRENT_SOURCE_DIR}/libs/linux/static
	)
elseif(WIN32)
	list(APPEND
			ENGINE_SOURCES
			src/memory/memory_windows.c
	)
	target_link_directories(engine PUBLIC
			${CMAKE_CURRENT_SOURCE_DIR}/libs/windows/dynamic
			${CMAKE_CURRENT_SOURCE_DIR}/libs/windows/static
	)
endif()

target_sources(engine PRIVATE ${ENGINE_SOURCES})

target_include_directories(engine PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/headers
)
target_link_libraries(engine
		PUBLIC
		glad
		glfw3
)

if(UNIX)
	target_link_libraries(engine PRIVATE m dl)
elseif(WIN32)
	target_link_libraries(engine PRIVATE opengl32)
endif()

add_library(glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/src/glad/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers/external)

