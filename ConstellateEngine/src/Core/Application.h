#pragma once


#include "Platform/Windows/WindowWindow.h"
#include "Core/Window.h"

namespace csl {
	class Application {
	private:
		std::unique_ptr<Window> _window;
		bool _running = true;
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in CLIENT and used in ENTRY POINT
	Application* CreateApplication();
}