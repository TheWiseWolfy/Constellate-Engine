project (ConstellateEngine VERSION 1.0)


add_library("${PROJECT_NAME}" SHARED "src/Constellate.h" "src/Core/Core.h" "src/Core/Application.h" "src/Core/Application.cpp" "src/Core/EntryPoint.h")

target_include_directories("${PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")