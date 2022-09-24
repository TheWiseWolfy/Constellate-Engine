project (ConstellateEngine VERSION 1.0)

add_library("${PROJECT_NAME}" SHARED  "src/Core/Log.cpp" "src/Core/Application.cpp"   "src/Core/Window.h" "src/Platform/Windows/WindowWindow.cpp" "src/Events/ApplicationEvent.h")

target_precompile_headers("${PROJECT_NAME}" PRIVATE "src/cslpch.h")

target_include_directories("${PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")