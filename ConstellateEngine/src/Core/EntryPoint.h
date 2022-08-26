#pragma once

#ifdef CSL_PLATFORM_WINDOWS

extern csl::Application* csl::CreateApplication();

#include <iostream>

int main() {
	std::cout << "Created entry point.";
	auto* app = csl::CreateApplication();
	app->Run();
	delete app;
}

#endif