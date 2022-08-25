project (ConstellateEngine VERSION 1.0)


add_library("${PROJECT_NAME}" SHARED
		"src/test.h"
		"src/test.cpp"
)

target_include_directories("${PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")