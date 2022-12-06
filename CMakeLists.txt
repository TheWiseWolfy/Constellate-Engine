cmake_minimum_required(VERSION 3.23.1)

project (ConstellateProject VERSION 1.0)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)     #Required for exporting the symbols in DLLs
#set( CMAKE_VERBOSE_MAKEFILE on )   #Makes it so you can see the final linker command created by CMake
set(CMAKE_CXX_STANDARD 17)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")   #Put the libraryes and executable in the same place
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

#we make sure the dll and game run in the same c enviroment and share a heap.

#set(CMAKE_CXX_FLAGS_DEBUG "/MDd")
#set(CMAKE_CXX_FLAGS_RELEASE "/MD")


#set(GLFW_INCLUDE_NONE 1) not sure yet if needed

add_compile_definitions(CSL_PLATFORM_WINDOWS)
add_compile_definitions(CSL_ENABLE_ASSERTS)

#libraries
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui)

add_subdirectory(ConstellateEngine) 

target_link_libraries("ConstellateEngine" glfw)
target_link_libraries("ConstellateEngine" spdlog)
target_link_libraries("ConstellateEngine" Glad)
target_link_libraries("ConstellateEngine" imgui)

target_include_directories("ConstellateEngine" PUBLIC "${PROJECT_SOURCE_DIR}/vendor/spdlog/include")
target_include_directories("ConstellateEngine" PUBLIC "${PROJECT_SOURCE_DIR}/vendor/glfw/include")
target_include_directories("ConstellateEngine" PUBLIC "${PROJECT_SOURCE_DIR}/vendor/glad/include")
target_include_directories("ConstellateEngine" PUBLIC "${PROJECT_SOURCE_DIR}/vendor/imgui")

#_________________________

add_subdirectory(Game)
target_link_libraries("Game" PRIVATE "ConstellateEngine")

#This is a hell that will never leave me alone.
#set_property(TARGET Game PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL$<$<CONFIG:Debug>:Debug>")
#set_property(TARGET ConstellateEngine PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL$<$<CONFIG:Debug>:Debug>")