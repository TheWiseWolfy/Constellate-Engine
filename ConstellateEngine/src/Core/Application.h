#pragma once


#include "Platform/Windows/WindowWindow.h"
#include "Core/Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Layer/LayerStack.h"

#include "Renderer/Shader.h"

namespace csl {
	class Application {
	private:
		std::unique_ptr<Window> _window;
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

		unsigned int _VertexArray, _VertexBuffer, _IndexBuffer;

		std::unique_ptr<Shader> _shader;
	};

	//To be defined in CLIENT and used in ENTRY POINT
}