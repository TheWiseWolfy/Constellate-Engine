
cmake_minimum_required(VERSION 3.23.1)

project (ConstellateProject VERSION 1.0)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON) 

add_library(ConstellateEngine SHARED
		"src/test.h"
		"src/test.cpp"
		)

add_executable("${PROJECT_NAME}" "main.cpp")

target_link_libraries("${PROJECT_NAME}" PRIVATE "ConstellateEngine")