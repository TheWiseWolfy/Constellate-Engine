#include "Application.h"
#include "Log.h"

namespace csl {
	Application::Application(){
		_window = std::unique_ptr<Window>(Window::Create());
		_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application(){

	}


	void Application::OnEvent(EngineEvent& e){
		EventDispatcher dispatcher(e);
		dispatcher.Dispach<WindowCloseEvent>(std::bind( &Application::OnWindowClose, this, std::placeholders::_1) );

		CSL_CORE_TRACE("{0}", e.ToString() );
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		_running = false;
		return true;
	}


	void Application::Run(){
		while (_running)
		{
			_window->OnUpdate();
		}
	}


}