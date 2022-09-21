

#include "cslpch.h"

#include "WindowWindow.h"
#include "Core/Log.h"

namespace csl{

	static bool s_GLFWInitialized = false;

	//This will define the way the application windows will be created
	std::unique_ptr<Window> Window::Create(const WindowDetails& props) {
		return std::make_unique<WindowsWindow>(props);
	}
	
	WindowsWindow::WindowsWindow(const WindowDetails& props) {
		_data.Title = props.Title;
		_data.Width = props.Width;
		_data.Height = props.Height;


		CSL_CORE_TRACE("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			CSL_CORE_ASSERT(success, "Could not intialize GLFW!");

			s_GLFWInitialized = true;
		}

		_window = glfwCreateWindow((int)_data.Width, (int)_data.Height, _data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(_window);
		glfwSetWindowUserPointer(_window, &_data);   //We store a arbitrary pointer in asociation with our window.
		SetVSync(false);
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(_window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(_window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		_data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return _data.VSync;
	}


}