project (ConstellateEngine VERSION 1.0)

add_library("${PROJECT_NAME}" SHARED  "src/Core/Log.cpp" "src/Core/Application.cpp"   "src/Core/Window.h" "src/Platform/Windows/WindowWindow.cpp" "src/Events/ApplicationEvent.h" "src/Layer/Layer.h" "src/Layer/Layer.cpp" "src/Layer/LayerStack.h" "src/Layer/LayerStack.cpp" "src/gui/ImGuiLayer.h"  "src/Gui/ImGuiLayer.cpp" "src/Platform/OpenGL/imgui_impl_opengl3.cpp" "src/Platform/OpenGL/imgui_impl_opengl3.h")

#target_precompile_headers("${PROJECT_NAME}" PRIVATE "src/cslpch.h")  #Precompile headers, very funky when makind lots of changes

target_include_directories("${PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")