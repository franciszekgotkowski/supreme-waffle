add_library(engine STATIC)

set(ENGINE_SOURCES
    # src/engine.c
    # src/renderer.c
    src/print.c
)

if(UNIX)
    list(APPEND ENGINE_SOURCES
        # src/platform/platform_linux.c
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
