#pragma once


#include "Platform/Windows/WindowWindow.h"
#include "Core/Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Layer/LayerStack.h"


#include "Renderer/RendererCommand.h"

namespace csl {
	class Application {
	private:
		std::unique_ptr<Window> _window;
		RendererCommand* _renCom;

		LayerStack _layerStack;
		bool _running = true;
		static Application* _instance;

		bool OnWindowClose(WindowCloseEvent& e);

	public:
		Application();
	
		
		virtual ~Application();

		void Run();
		void OnEvent(EngineEvent& e);
		Window& GetWindow() { return *_window; }

		void PushLayer(Layer* layer);
		
		static Application& GetInstance() { return *_instance; }
		static Application* CreateApplication();

	
	};

	//To be defined in CLIENT and used in ENTRY POINT
}