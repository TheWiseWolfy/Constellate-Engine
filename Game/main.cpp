#include <iostream>

#include <Constellate.h>
#include <iostream>

using namespace csl;

class ExampleLayer : public Layer
{
public:
	ExampleLayer(): Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//CSL_TRACE("ExampleLayer::Update");
	}

	void OnEvent(EngineEvent& event) override
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispach<MouseMovedEvent>(std::bind(&ExampleLayer::OnMouseMoved, this, std::placeholders::_1));
		dispatcher.Dispach<KeyPressedEvent>(std::bind(&ExampleLayer::OnKeyPressed, this, std::placeholders::_1));

		//CSL_TRACE("ExampleLayer::Event");


	}

	bool _firstMouse = true;
	float lastX = 0;
	float lastY = 0;

	bool OnKeyPressed(KeyPressedEvent& e) {

		glm::vec3 poz = Application::GetInstance()._renCom->GetCameraPosition();

		if (e.GetKeyCode() == 87 ) {
			poz.z -= 0000.1;
		}

		if (e.GetKeyCode() == 83) {
			poz.z += 0000.1;
		}

		if (e.GetKeyCode() == 65) {
			poz.x -= 0000.1;
		}

		if (e.GetKeyCode() == 68) {
			poz.x += 0000.1;
		}
		 
		if (e.GetKeyCode() == 90) {
			poz.y += 0000.1;
		}

		if (e.GetKeyCode() == 88) {
			poz.y -= 0000.1;
		}


		Application::GetInstance()._renCom->SetCameraPosition(poz);

		return false;
	}


	bool OnMouseMoved(MouseMovedEvent& e) {

		float xpos = e.GetX();
		float ypos = e.GetY();

		if (_firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			_firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		ProcessMouseMovement(xoffset, yoffset);
		return true;
	}

	float Yaw = 0;
	float Pitch = 0;
	// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true , float mouseSensitivity = 0.1f)
	{
		// euler Angles
	
		xoffset *= mouseSensitivity;
		yoffset *= mouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// update Front, Right and Up Vectors using the updated Euler angles
		Application::GetInstance()._renCom->SetCameraRotation(glm::vec2(Yaw, Pitch));

	}
};

class Game : public Application {

public:
	Game() {
		PushLayer(new ExampleLayer());
		PushLayer(new ImGuiLayer());


	}
	~Game(){

	}
};

//This is the entry point of the library
Application* Application::CreateApplication()
{
	return new Game();
}