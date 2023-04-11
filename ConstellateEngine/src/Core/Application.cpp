#include "Application.h"
#include "Log.h"

#include "GLFW/glfw3.h"
#include <glad/glad.h> //Look buddy, sometimes around february, GLFW became dependend on this exact include, so you won't be able to delete it anymore.



namespace csl {
	 
	Application* Application::_instance = nullptr;

	//PUBLIC INTERFACE FUCTIONS
	Application::Application(){
		_instance = this;
		
		_window = std::unique_ptr<Window>(Window::Create());
		_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		_entityManager = std::make_unique<EntityManager>();
		_rendererManager = std::make_unique<RendererManager>();
	}

	Application::~Application(){

	}

	void Application::PushLayer(Layer* layer)
	{
		_layerStack.PushLayer(layer);
		layer->OnAttach();
	}



	void Application::Run() {
		while (_running)
		{
			//this is also temporary 
			_rendererManager->DrawGame();

			for (Layer* layer : _layerStack) {
				layer->OnUpdate();
			}
			_window->OnUpdate();
		}
	}

	void Application::OnEvent(EngineEvent& e) {
		EventDispatcher dispatcher(e);

		dispatcher.Dispach<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		for (auto it = _layerStack.end(); it != _layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}

		CSL_CORE_LOG("{0}", e.ToString());
	}

	//PRIVATE EVENT CALLBACKS
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		_running = false;
		return true;
	}
}