#pragma once


#ifdef CSL_PLATFORM_WINDOWS

	extern csl::Application* csl::CreateApplication();

	#include <Core/Log.h>

	int main() {
		csl::Log::Init();

		CSL_CORE_INFO("Created entry point.");

		auto* app = csl::CreateApplication();
		app->Run();
		delete app;
	}

#endif