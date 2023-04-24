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

		glm::vec3 poz = Application::GetInstance().GetRenderer().GetCameraPosition();

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


		Application::GetInstance().GetRenderer().SetCameraPosition(poz);

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

		// Wrap the mouse input so that it continues to rotate the camera
		int windowHeight = Application::GetInstance().GetWindow().GetHeigth();
		int windowWidth = Application::GetInstance().GetWindow().GetWidth();

		Application::GetInstance().GetWindow().SetMousePosition(windowWidth / 2, windowHeight / 2);
		lastX = windowWidth / 2;
		lastY = windowHeight / 2;

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
		Application::GetInstance().GetRenderer().SetCameraRotation(glm::vec2(Yaw, Pitch));

	}
};

class Game : public Application {

public:
	Game() {
		PushLayer(new ExampleLayer());
		PushLayer(new ImGuiLayer());

		{
			Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
			const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\pillarobj.obj");
			EntityFactory::SceneToEntityHierachy(scene, entity);
			//const aiScene* sceneCube = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\cube.obj");
			entity->addComponent<SphereCollider>(1.3f);
			entity->addComponent<PhysicsComponent>();
			entity->setTransform(Transform(glm::vec3(4, 1, -5)));
		}


		{
			Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
			const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\pillarobj.obj");
			EntityFactory::SceneToEntityHierachy(scene, entity);
			//const aiScene* sceneCube = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\cube.obj");
			entity->addComponent<SphereCollider>(1.3f);
			entity->addComponent<PhysicsComponent>();
			entity->setTransform(Transform(glm::vec3(7, 1, -5)));
		}


		{
			Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
			const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\floor.obj");
			EntityFactory::SceneToEntityHierachy(scene, entity);
			//const aiScene* sceneCube = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\cube.obj");
		 	entity->addComponent<PlaneColider>(glm::vec3 ( 0.0, 1.0, 0.0 ) );
			auto& physics = entity->addComponent<PhysicsComponent>();
			physics.setStatic(true);
			entity->setTransform(Transform(glm::vec3(0, -3, 0)));

		}


		{
		Entity* entity3 = Application::GetInstance().GetEntityManager().addEntity();
		const aiScene* scene3 = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\pillar2.obj");
		EntityFactory::SceneToEntityHierachy(scene3, entity3);
		}
	
		{
			Entity* entity4 = Application::GetInstance().GetEntityManager().addEntity();
			const aiScene* scene4 = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\trueHidrant.obj");
			EntityFactory::SceneToEntityHierachy(scene4, entity4);
			entity4->setTransform(Transform(glm::vec3(4, 0, 0), glm::vec3(5, 5, 5)));
		}
	}
	~Game(){

	}
};

//This is the entry point of the library
Application* Application::CreateApplication()
{
	return new Game();
}