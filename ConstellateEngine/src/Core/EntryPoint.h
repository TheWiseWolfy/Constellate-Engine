/*
File:EntryPoint.h

A technique that makes it so the library compiles main first, efectivly taking ownership of it.

Credit: https://github.com/TheCherno/Hazel
*/
#pragma once

#ifdef CSL_PLATFORM_WINDOWS

	#include <Core/Log.h>

	int main() {
		csl::Log::Init();

		CSL_CORE_INFO("Created entry point.");

		auto* app = csl::Application::CreateApplication();
		app->Run();
		delete app;
	}

#endif