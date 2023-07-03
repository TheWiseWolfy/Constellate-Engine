#pragma once

#include "Gui/ImGuiLayer.h"
#include "imgui.h"

using namespace csl;


class MyGUILayer : public ImGuiLayer {
private:
	int _points = 0;
public:

	void Display() override {
		ImGui::Text("My Points: %d" , _points);
	}

	void SetPoints(int points) {
		_points = points;
	}
};