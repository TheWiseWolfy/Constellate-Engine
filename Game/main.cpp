#include <iostream>

#include <Constellate.h>
#include <iostream>

class ExampleLayer : public csl::Layer
{
public:
	ExampleLayer(): Layer("Example")
	{
	}

	void OnUpdate() override
	{
		CSL_TRACE("ExampleLayer::Update");
	}

	void OnEvent(csl::EngineEvent& event) override
	{
		CSL_TRACE("ExampleLayer::Event");
	}
};

class Game : public csl::Application {

public:
	Game() {
		PushLayer(new ExampleLayer());
	}
	~Game(){

	}
};

//This is the entry point of the library
csl::Application* csl::Application::CreateApplication()
{
	return new Game();
}