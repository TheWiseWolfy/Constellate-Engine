#include "Application.h"
#include "spdlog/spdlog.h"


namespace csl {
	Application::Application()
	{
		spdlog::warn("Easy padding in numbers like {:08d}", 12);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (true)
		{

		}
	}
}