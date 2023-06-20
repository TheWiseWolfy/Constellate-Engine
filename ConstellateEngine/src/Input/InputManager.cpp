#include "InputManager.h"

#include "Core/Application.h"

namespace csl {
    InputManager* InputManager::instance = nullptr;

     bool InputManager::isKeyPressed(int keyCode) {

        GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());


        int state = glfwGetKey(window, keyCode);
        return state == GLFW_PRESS;
    }

}