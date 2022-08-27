#pragma once

namespace csl {
	class Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in CLIENT and used in ENTRY POINT
	Application* CreateApplication();
}