#include "ImGuiLayer.h"
#include "cslpch.h"

#include "imgui.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"
#include "Core/Application.h"

namespace csl {

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {
	}

	ImGuiLayer::~ImGuiLayer() {
	}

	void ImGuiLayer::OnAttach(){
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags = ImGuiBackendFlags_HasMouseCursors | ImGuiBackendFlags_HasSetMousePos;

		Application& app = Application::GetInstance();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeigth());
		//Hey whatever

		ImGui_ImplOpenGL3_Init("#version 410");

		
	}

	void ImGuiLayer::OnDetach(){
	}

	void ImGuiLayer::OnUpdate() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		
		ImGui::Begin("Hello");
		ImGui::Text("Hello World");
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(EngineEvent& event) {
		
	}

}