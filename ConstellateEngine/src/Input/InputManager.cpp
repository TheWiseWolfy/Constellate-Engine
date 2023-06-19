#include "InputManager.h"

#include "Core/Application.h"

namespace csl {
    InputManager* InputManager::instance = nullptr;

     bool InputManager::isKeyPressed(int keyCode) {

        // return isKeyPressedImpl(keyCode);

        auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());


        auto state = glfwGetMouseButton(window, keyCode);
        return state == GLFW_PRESS;
    }

}