add_library(common STATIC)

set(COMMON_SOURCES
	src/string_utils.c
)

target_sources(common PRIVATE
	${COMMON_SOURCES}
)

target_include_directories(common PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/headers
)
