#pragma once

#include "RenderingContext.h"

struct GLFWwindow;

namespace csl {
	
	class OpenGlContext : public RenderingContext{
	public:
		OpenGlContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* _windowHandle;
	};
}