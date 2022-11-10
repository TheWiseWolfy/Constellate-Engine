#pragma once


#include "Platform/Windows/WindowWindow.h"
#include "Core/Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace csl {
	class Application {
	private:
		std::unique_ptr<Window> _window;
		bool _running = true;
	public:
		Application();

		virtual ~Application();

		void Run();
		void OnEvent(EngineEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);
	};

	//To be defined in CLIENT and used in ENTRY POINT
	extern Application* CreateApplication();
}