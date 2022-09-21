#include "Application.h"

namespace csl {
	Application::Application()
	{
		_window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (_running)
		{
			_window->OnUpdate();
		}
	}
}