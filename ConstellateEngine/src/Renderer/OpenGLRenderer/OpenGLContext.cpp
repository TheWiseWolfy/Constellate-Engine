#include "OpenGLContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Core/Core.h"
#include "Core/Log.h"



namespace csl {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : _windowHandle(windowHandle)
	{
		return;
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(_windowHandle);

        // Load OpenGL function pointers with Glad
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            CSL_CORE_LOG("Failed to initialize Glad");
            glfwTerminate();
            return;
        }

        // Retrieve and print GPU information
        const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
        if (renderer)
        {
            CSL_CORE_LOG("GPU: {0}", renderer);
        }
        else
        {
            CSL_CORE_LOG("Failed to retrieve GPU information");
        }

        
        return;
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(_windowHandle);
	}

}