project (Game VERSION 1.0)

set(CMAKE_BUILD_TYPE "Release")

add_executable("${PROJECT_NAME}" "main.cpp" "FirstPersonCamera.cpp" "FirstPersonCamera.h"    "TargetComponent.h" "TargetComponent.cpp"  "TargetHitEvent.h" "MyGUILayer.h")

