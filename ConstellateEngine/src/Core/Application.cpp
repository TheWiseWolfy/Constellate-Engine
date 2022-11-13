#include "Application.h"
#include "Log.h"

namespace csl {
	 
	Application* Application::_instance = nullptr;

	Application::Application(){
		_instance = this;
		
		_window = std::unique_ptr<Window>(Window::Create());
		_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application(){

	}

	void Application::OnEvent(EngineEvent& e){
		EventDispatcher dispatcher(e);
		dispatcher.Dispach<WindowCloseEvent>(std::bind( &Application::OnWindowClose, this, std::placeholders::_1) );


		for (auto it = _layerStack.end(); it != _layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}

		CSL_CORE_TRACE("{0}", e.ToString() );
	}

	void Application::PushLayer(Layer* layer)
	{
		_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		_running = false;
		return true;
	}

	void Application::Run(){
		while (_running)
		{
			//
			for (Layer* layer : _layerStack) {
				layer->OnUpdate();
			}
			_window->OnUpdate();
		}
	}


}