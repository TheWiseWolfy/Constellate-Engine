project (Game VERSION 1.0)

add_library("Glad" STATIC "src/glad.c")

target_include_directories("Glad" PUBLIC "${PROJECT_SOURCE_DIR}/include")

