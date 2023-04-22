#pragma once 

#include "cslpch.h"

#include "Core.h"
#include "Events/Event.h"

namespace csl {
	using EventCallbackFn = std::function<void(EngineEvent&)>;

	struct WindowDetails {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowDetails(const std::string& title = "Constellate Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	//Main window implementations for diffrent platforms and APIs
	class Window
	{
	public:

		virtual ~Window() {}
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeigth() const = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetMousePosition(int x, int y) = 0;

		static std::unique_ptr<Window> Create(const WindowDetails& props = WindowDetails());
	};
}