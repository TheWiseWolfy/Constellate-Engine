

#include "cslpch.h"
#include "glad/glad.h"

#include "WindowWindow.h"
#include "Core/Log.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Renderer/OpenGLContext.h"

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
		_context = new OpenGLContext(_window);
		_context->Init();
		
		glfwSetWindowUserPointer(_window, &_data);   //We store a arbitrary pointer in asociation with our window.
		SetVSync(false);

		//GLFW Callbacks 

		glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *( static_cast<WindowData*>(glfwGetWindowUserPointer(window) ) );  //Get a pointer we stored via glfw

			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(_window, [](GLFWwindow* window){
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			MouseButtonPressedEvent event(button);
			data.EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			MouseButtonReleasedEvent event(button);
			data.EventCallback(event);
			break;
		}
		}
			});


		glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});


	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(_window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();

		_context->SwapBuffers();

		
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