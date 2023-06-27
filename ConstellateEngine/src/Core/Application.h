#pragma once


#include "Platform/Windows/WindowWindow.h"
#include "Core/Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Layer/LayerStack.h"
#include "Renderer/RendererManager.h"
#include "Physics/PhysicsManager.h"
#include "Entity-Component/EntityManager.h"

namespace csl {
	class Application {
	private:
		std::unique_ptr<Window> _window;
		std::unique_ptr<PhysicsManager> _physicsManager;
		std::unique_ptr<RendererManager> _rendererManager;

		std::unique_ptr<EntityManager> _entityManager;

		LayerStack _layerStack;
		bool _running = true;
		static Application* _instance;

		bool OnWindowClose(WindowCloseEvent& e);

	public:

		Application();
		virtual ~Application();

		//Public interface fuctions
		void PushLayer(Layer* layer);
		
		void Run();

		//GETTERS
		static Application& GetInstance() { return *_instance; }
		Window& GetWindow() { return *_window; }

		RendererManager& GetRenderer() { return *_rendererManager; }
		EntityManager& GetEntityManager() { return *_entityManager; }

		void PublishEvent(EngineEvent& e);
		virtual void OnEventCallback(EngineEvent& e) {};


		//CREATION HANDLE - implemented in client
		static Application* CreateApplication();
	};

	//To be defined in CLIENT and used in ENTRY POINT
}