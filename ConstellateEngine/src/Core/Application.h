#pragma once


#include "Platform/Windows/WindowWindow.h"
#include "Core/Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Layer/LayerStack.h"

namespace csl {
	class Application {
	private:
		std::unique_ptr<Window> _window;
		LayerStack _layerStack;
		bool _running = true;

		bool OnWindowClose(WindowCloseEvent& e);
	public:
		Application();

		virtual ~Application();

		void Run();
		void OnEvent(EngineEvent& e);
		void PushLayer(Layer* layer);
		
		static Application* CreateApplication();
	};

	//To be defined in CLIENT and used in ENTRY POINT
}