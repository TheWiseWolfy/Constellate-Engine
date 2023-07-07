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

		ImGui::Text("Commands:\nW, S, A ,D - movement\nZ, X - up down\nM - lock mouse\nC-toggle gravity\nC-trow projectile\nB-create target\nV-stop player\nSPACE-jump player");


	}

	void SetPoints(int points) {
		_points = points;
	}
};