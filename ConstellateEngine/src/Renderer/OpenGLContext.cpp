#include "OpenGLContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Core/Core.h"

namespace csl {
	OpenGlContext::OpenGlContext(GLFWwindow* windowHandle) : _windowHandle(windowHandle)
	{
		
	}
	void OpenGlContext::Init()
	{
		glfwMakeContextCurrent(_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CSL_CORE_ASSERT(status, "Failed to initialize Glad!");
	}

	void OpenGlContext::SwapBuffers()
	{
		glfwSwapBuffers(_windowHandle);
	}

}