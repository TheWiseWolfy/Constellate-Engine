project (ConstellateEngine VERSION 1.0)

#add_library("${PROJECT_NAME}" STATIC 
#"src/Core/Log.cpp" "src/Core/Core.h" 
#"src/Core/Application.cpp"   
#"src/Platform/Windows/WindowWindow.cpp"
#"src/Events/ApplicationEvent.h" "src/Layer/Layer.h"
#"src/Layer/Layer.cpp" 
#"src/Layer/LayerStack.cpp" 
#"src/Gui/ImGuiLayer.cpp" 
#"src/Platform/OpenGL/imgui_impl_opengl3.cpp"
#"src/Platform/OpenGL/imgui_impl_opengl3.h"
#"src/Events/MouseEvent.h" "src/Renderer/RenderingContext.h"
#"src/Renderer/OpenGLContext.h"
#"src/Renderer/OpenGLContext.cpp" 
#"src/Renderer/Shader.cpp" 
#"src/Renderer/RenderBuffer.cpp"
#"src/Platform/OpenGL/OpenGLBuffer.h"
#"src/Platform/OpenGL/OpenGLBuffer.cpp"
#"src/Renderer/Renderer.cpp"
#"src/Renderer/VertexArray.cpp"
#"src/Renderer/OpenGlRenderer/OpenGLVertexArray.h"
#)



file(GLOB_RECURSE  csl_src CONFIGURE_DEPENDS
     "*.h"
     "*.cpp"
)

add_library("${PROJECT_NAME}" STATIC ${csl_src}  "src/Resources/AssetImporter.h"  "src/Physics/CollisionDetection.cpp")

target_include_directories("${PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
