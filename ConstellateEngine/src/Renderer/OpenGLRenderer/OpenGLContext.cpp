#include "OpenGLContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Core/Core.h"



namespace csl {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : _windowHandle(windowHandle)
	{
		return;
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CSL_CORE_ASSERT(status, "Failed to initialize Glad!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(_windowHandle);
	}

}