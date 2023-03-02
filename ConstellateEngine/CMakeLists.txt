project (ConstellateEngine VERSION 1.0)

add_library("${PROJECT_NAME}" STATIC "src/Core/Log.cpp" "src/Core/Core.h"  "src/Core/Application.cpp"   "src/Core/Window.h" "src/Platform/Windows/WindowWindow.cpp" "src/Events/ApplicationEvent.h" "src/Layer/Layer.h" "src/Layer/Layer.cpp" "src/Layer/LayerStack.h" "src/Layer/LayerStack.cpp" "src/gui/ImGuiLayer.h"  "src/Gui/ImGuiLayer.cpp" "src/Platform/OpenGL/imgui_impl_opengl3.cpp" "src/Platform/OpenGL/imgui_impl_opengl3.h" "src/Events/MouseEvent.h" "src/Renderer/RenderingContext.h" "src/Renderer/OpenGLContext.h" "src/Renderer/OpenGLContext.cpp" "src/Renderer/Shader.h" "src/Renderer/Shader.cpp")

target_include_directories("${PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

