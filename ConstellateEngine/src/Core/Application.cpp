/*
File: Application.cpp

TODO: Implement propper key pooling in order to capture key presses sincroniusly

This class is the central featre of CSL Engine, so it holds all the managers and all engine fuctionality goes though it.
*/

#include "Application.h"
#include "Log.h"

#include "GLFW/glfw3.h"
#include <glad/glad.h> 

namespace csl {
	 
	Application* Application::_instance = nullptr;

	//PUBLIC INTERFACE FUCTIONS
	Application::Application(){
		_instance = this;
		
		_window = std::unique_ptr<Window>(Window::Create());
		_window->SetEventCallback(std::bind(&Application::PublishEvent, this, std::placeholders::_1));

		_entityManager = std::make_unique<EntityManager>();
		_rendererManager = std::make_unique<RendererManager>();
		_physicsManager = std::make_unique<PhysicsManager>();
	}

	Application::~Application(){

	}

	void Application::PushLayer(Layer* layer)
	{
		_layerStack.PushLayer(layer);
		layer->OnAttach();
	}


	void Application::Run() {
		auto lastTime = std::chrono::high_resolution_clock::now();

		while (_running)
		{
			//Calculate delta time
			const float targetFrameTime = 1.0f / 60.0f; // Target frame time 

			auto now =  std::chrono::steady_clock::now();
			float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastTime).count() / 1000000.0f;
			lastTime = now;

			//CSL_CORE_LOG("Frame time:{0}", deltaTime);

			_entityManager->update(deltaTime);
			_physicsManager->calculatePhysics(deltaTime);
			_rendererManager->DrawGame();

			for (Layer* layer : _layerStack) {
				layer->OnUpdate();
			}
			_window->OnUpdate();

			float sleepTime = abs(targetFrameTime - deltaTime);

			if (sleepTime > 0) {
				std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime));
			}
		}
	}

	//This is the entry point for all the events in the game
	void Application::PublishEvent(EngineEvent& e) {
		EventDispatcher dispatcher(e);

		dispatcher.Dispach<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		for (auto it = _layerStack.end(); it != _layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}

		_entityManager->propagateEvent(e);

		if ( e.ToString().find("Mouse") == std::string::npos) {
			CSL_CORE_LOG("{0}", e.ToString());
		}
		OnEventCallback(e);
	}

	//PRIVATE EVENT CALLBACKS
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		_running = false;
		return true;
	}
}