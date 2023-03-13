#pragma once


#include "Platform/Windows/WindowWindow.h"
#include "Core/Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Layer/LayerStack.h"
#include "Renderer/RendererController.h"

namespace csl {
	class Application {
	private:
		std::unique_ptr<Window> _window;

		LayerStack _layerStack;
		bool _running = true;
		static Application* _instance;

		bool OnWindowClose(WindowCloseEvent& e);
	public:
		std::unique_ptr<RendererController> _renCom;

		Application();
		virtual ~Application();

		//Public interface fuctions
		void PushLayer(Layer* layer);
		
		void Run();
		void OnEvent(EngineEvent& e);

		//GETTERS
		static Application& GetInstance() { return *_instance; }
		Window& GetWindow() { return *_window; }

		//CREATION HANDLE - implemented in client
		static Application* CreateApplication();
	};

	//To be defined in CLIENT and used in ENTRY POINT
}