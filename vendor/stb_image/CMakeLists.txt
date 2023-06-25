project (stb_image VERSION 1.0)

add_library("stb_image" STATIC)

target_include_directories("stb_image" PUBLIC "${PROJECT_SOURCE_DIR}/include")

