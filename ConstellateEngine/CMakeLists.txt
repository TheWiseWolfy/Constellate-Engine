project (ConstellateEngine VERSION 1.0)

add_library("${PROJECT_NAME}" SHARED  "src/Core/Log.cpp" "src/Core/Application.cpp"  "src/Core/Core.h")

target_include_directories("${PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")