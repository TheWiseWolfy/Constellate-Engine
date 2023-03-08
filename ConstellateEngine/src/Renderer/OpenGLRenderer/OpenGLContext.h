#pragma once

#include "Renderer/RenderingContext.h"

struct GLFWwindow;

namespace csl {
	
	class OpenGLContext : public RenderingContext{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* _windowHandle;
	};
}