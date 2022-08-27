cmake_minimum_required(VERSION 3.23.1)

project (ConstellateProject VERSION 1.0)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)     #Required for exporting the symbols in DLLs
#set( CMAKE_VERBOSE_MAKEFILE on )   #Makes it so you can see the final linker command created by CMake
set(CMAKE_CXX_STANDARD 17)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")   #Put the libraryes and executable in the same place
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")


add_compile_definitions(CSL_PLATFORM_WINDOWS)

add_subdirectory(spdlog)
add_subdirectory(ConstellateEngine) 

#spdlog library
target_link_libraries("ConstellateEngine" PRIVATE spdlog::spdlog)
target_include_directories("ConstellateEngine" PUBLIC "${PROJECT_SOURCE_DIR}/spdlog/include")

#_________________________

add_subdirectory(Game)
target_link_libraries("Game" PRIVATE "ConstellateEngine")










