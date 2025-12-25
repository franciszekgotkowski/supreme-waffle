add_library(engine STATIC)

set(ENGINE_SOURCES
	src/main.c
)

if(UNIX)
	list(APPEND 
        ENGINE_SOURCES
	    src/memory/memory_linux.c
)
elseif(WIN32)
	list(APPEND ENGINE_SOURCES
	# src/platform/platform_win32.c
)
elseif(APPLE)
	list(APPEND ENGINE_SOURCES
	# src/platform/platform_macos.c
)
endif()

target_sources(engine PRIVATE ${ENGINE_SOURCES})

target_include_directories(engine PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/headers
)

target_link_directories(engine PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/libs/dynamic
	${CMAKE_CURRENT_SOURCE_DIR}/libs/static
)

target_link_libraries(engine
	PUBLIC
	glad
	PRIVATE
    glfw3
	m
	dl
)

add_library(glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/src/glad/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers/external)

