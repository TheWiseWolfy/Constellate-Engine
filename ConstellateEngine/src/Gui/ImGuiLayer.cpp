#include "ImGuiLayer.h"
#include "imgui.h"
#include "cslpch.h"

#define IM
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

		//ImGui_ImplGlfw_InitForOpenGL(window, true); this is a rabbit whole not worth going into

		ImGui_ImplOpenGL3_Init("#version 410");

		
	}

	void ImGuiLayer::OnDetach(){
	}

	void ImGuiLayer::OnUpdate() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		
		//ImGui::Begin("Hello");
		//ImGui::Text("Hello World");
		ImGui::Begin("Hello");
		Display();
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::Display() {
		ImGui::Begin("Hello");
		ImGui::Text("This is the test UI");
	}

	void ImGuiLayer::OnEvent(EngineEvent& event) {

		EventDispatcher dispacher(event);

		dispacher.Dispach<MouseButtonPressedEvent>(
			std::bind( &ImGuiLayer::OnMouseButtonPressedEvent, this, std::placeholders::_1));

		dispacher.Dispach<MouseButtonReleasedEvent>(
			std::bind(&ImGuiLayer::OnMouseButtonReleasedEvent, this, std::placeholders::_1));

		dispacher.Dispach<MouseMovedEvent>(
			std::bind(&ImGuiLayer::OnMouseMovedEvent, this, std::placeholders::_1));

		dispacher.Dispach<MouseScrolledEvent>(
			std::bind(&ImGuiLayer::OnMouseScrolledEvent, this, std::placeholders::_1));

		dispacher.Dispach<KeyPressedEvent>(
			std::bind(&ImGuiLayer::OnKeyPressedEvent, this, std::placeholders::_1));

		dispacher.Dispach<KeyReleasedEvent>(
			std::bind(&ImGuiLayer::OnKeyReleasedEvent, this, std::placeholders::_1));

		dispacher.Dispach<KeyTypedEvent>(
			std::bind(&ImGuiLayer::OnKeyTypedEvent, this, std::placeholders::_1));

		dispacher.Dispach<WindowResizeEvent>(
			std::bind(&ImGuiLayer::OnWindowResizeEvent, this, std::placeholders::_1));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		return false;
	}

}