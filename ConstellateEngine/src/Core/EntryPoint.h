#pragma once


#ifdef CSL_PLATFORM_WINDOWS

	extern csl::Application* csl::CreateApplication();

	#include <iostream>

	int main() {
		csl::Log::Init();
		csl::Log::GetCoreLogger()->warn("Mom, I'm ultra scared.");

		std::cout << "Created entry point.";
		auto* app = csl::CreateApplication();
		app->Run();
		delete app;
	}

#endif