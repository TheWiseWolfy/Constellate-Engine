#pragma once

#include "Layer/Layer.h"
//#include "imgui/imgui.h"

namespace csl {

	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
			
		void OnUpdate();
		void OnEvent(EngineEvent& event);

	};

	
}