#pragma once

#include "Core/Window.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "Renderer/RenderingContext.h"

namespace csl {

	struct WindowData {				
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		bool VSync;

		EventCallbackFn EventCallback;
	};

	class WindowsWindow : public Window {
		private: 
			GLFWwindow* _window;
			RenderingContext* _context;
			WindowData _data;
		public:
			WindowsWindow(const WindowDetails& prop);
			virtual ~WindowsWindow();
	 
			void OnUpdate() override;
	
			inline unsigned int GetWidth() const override { return _data.Width; }
			inline unsigned int GetHeigth() const override { return _data.Height; }
			void SetVSync(bool enabled) override;
			bool IsVSync() const override;

			//Wondow attributes
			void SetEventCallback(const EventCallbackFn& callback) override { _data.EventCallback = callback; }
			
	};
}


