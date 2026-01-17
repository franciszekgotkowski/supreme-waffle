add_executable(bdf_converter
        src/main.c
        src/string_utils.c
)

target_sources(bdf_converter PRIVATE
)

target_include_directories(bdf_converter PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

target_link_directories(bdf_converter PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/dynamic
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/static
)


target_link_libraries(bdf_converter
        stb_bdf
)



add_library(stb_bdf STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/src/stb/stb_image.c
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/src/stb/stb_image_write.c
)

target_include_directories(stb_bdf PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
)
