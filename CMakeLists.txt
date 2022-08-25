cmake_minimum_required(VERSION 3.23.1)

project (ConstellateProject VERSION 1.0)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)     #Required for exporting the symbols in DLLs

set( CMAKE_VERBOSE_MAKEFILE on )   #Makes it so you can see the final linker command created by CMake

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")   #Put the library and executable in the same place
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(ConstellateEngine) 
add_subdirectory(Game)

target_link_libraries("Game" PRIVATE "ConstellateEngine")