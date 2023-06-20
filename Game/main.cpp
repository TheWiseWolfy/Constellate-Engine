 #include <iostream>

#include <Constellate.h>
#include <iostream>
#include <random>
#include <chrono>

#include "FirstPersonCamera.h"
#include "PlayerComponent.h"

using namespace csl;


class Game : public Application {
private: 

	bool _firstMouse = true;
	float _lastX = 0;
	float _lastY = 0;
	FPCamera _camera;
public:
	Game() {
		PushLayer(new ImGuiLayer());


		TestFuction();
	}
	~Game(){
		
	}

	void OnEventCallback(EngineEvent& e) override {

		EventDispatcher dispatcher(e);

		dispatcher.Dispach<MouseMovedEvent>(std::bind(&Game::OnMouseMoved, this, std::placeholders::_1));
		dispatcher.Dispach<KeyPressedEvent>(std::bind(&Game::OnKeyPressed, this, std::placeholders::_1));
	};


	bool OnKeyPressed(KeyPressedEvent& e) {

		glm::vec3 poz = Application::GetInstance().GetRenderer().GetCameraPosition();

		if (e.GetKeyCode() == CSL_KEY_W) {
			poz += _camera.getCameraDirection() * 0.1f;
		}

		if (e.GetKeyCode() == CSL_KEY_S) {
			poz -= _camera.getCameraDirection() * 0.1f;
		}

		if (e.GetKeyCode() == CSL_KEY_A) {
			poz -= _camera.getRightVector() * 0.1f;

		}

		if (e.GetKeyCode() == CSL_KEY_D) {
			poz += _camera.getRightVector() * 0.1f;
		}

		if (e.GetKeyCode() == CSL_KEY_Z) {
			poz.y += 0.1;
		}

		if (e.GetKeyCode() == CSL_KEY_X) {
			poz.y -= 0.1;
		}

		if (e.GetKeyCode() == CSL_KEY_C) {
			{
				//_________________

				Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
				const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\sphere.obj");
				EntityFactory::SceneToEntityHierachy(scene, entity);
				//const aiScene* sceneCube = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\cube.obj");
				entity->addComponent<SphereCollider>(1.f);
				PhysicsComponent& phycomp = entity->addComponent<PhysicsComponent>();
				entity->addComponent<PlayerComponent>(_camera);


				phycomp.applyForce(_camera.getCameraDirection() * 20.0f);
			
				entity->setTransform( Transform(poz) );
			}
		}

		Application::GetInstance().GetRenderer().SetCameraPosition(poz);

		return false;
	}


	bool OnMouseMoved(MouseMovedEvent& e) {

		float xpos = e.GetX();
		float ypos = e.GetY();

		if (_firstMouse) {
			_lastX = xpos;
			_lastY = ypos;
			_firstMouse = false;
		}

		float xoffset = xpos - _lastX;
		float yoffset = _lastY - ypos; // reversed since y-coordinates go from bottom to top

		_lastX = xpos;
		_lastY = ypos;

		// Wrap the mouse input so that it continues to rotate the camera
		int windowHeight = Application::GetInstance().GetWindow().GetHeigth();
		int windowWidth = Application::GetInstance().GetWindow().GetWidth();

		_lastX = windowWidth / 2;
		_lastY = windowHeight / 2;

		_camera.ProcessMouseMovement(xoffset, yoffset);

		Application::GetInstance().GetRenderer().SetCameraRotation(_camera.getYaw(), _camera.getPitch());
		//The mouse gets stuck in the middle of the window to accomoate the camera.
		Application::GetInstance().GetWindow().SetMousePosition(windowWidth / 2, windowHeight / 2);

		return true;
	}

	void TestFuction() {
		{
			Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
			const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\sphere.obj");
			EntityFactory::SceneToEntityHierachy(scene, entity);
			//const aiScene* sceneCube = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\cube.obj");
			entity->addComponent<SphereCollider>(1.f);
			entity->addComponent<PhysicsComponent>();
			entity->addComponent<PlayerComponent>(_camera);

			entity->setTransform(Transform(glm::vec3(4.5, 7, -5.5)));
		}

		{
			Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
			const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\sphere.obj");
			EntityFactory::SceneToEntityHierachy(scene, entity);
			//const aiScene* sceneCube = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\cube.obj");
			entity->addComponent<SphereCollider>(1.f);
			entity->addComponent<PhysicsComponent>();
			entity->setTransform(Transform(glm::vec3(7, 1, -5.8)));
		}


		{
			Entity* entity = Application::GetInstance().GetEntityManager().addEntity();

			entity->addComponent<SphereCollider>(1.f);
			entity->addComponent<PhysicsComponent>();
			//here entity->addComponent<RendererComponent>() is called

			const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\sphere.obj");
			EntityFactory::SceneToEntityHierachy(scene, entity);

			entity->setTransform(Transform(glm::vec3(4, 5, -5)));
		}


		{
			Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
			const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\floor.obj");
			EntityFactory::SceneToEntityHierachy(scene, entity);
			//const aiScene* sceneCube = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\cube.obj");
			entity->addComponent<PlaneColider>(glm::vec3(0.0, 1.0, 0.0));
			auto& physics = entity->addComponent<PhysicsComponent>();
			physics.setStatic(true);
			entity->setTransform(Transform(glm::vec3(0, -3, 0)));
		}


		{
			Entity* entity3 = Application::GetInstance().GetEntityManager().addEntity();

			//TODO Rotation matrix thingy
			const aiScene* scene3 = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\13466_Canaan_Dog_v1_L3.obj");
			entity3->setTransform(Transform(glm::vec3(0, 20, 0)));

			EntityFactory::SceneToEntityHierachy(scene3, entity3);
		}


		{
			Entity* entity4 = Application::GetInstance().GetEntityManager().addEntity();
			const aiScene* scene4 = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\trueHidrant.obj");
			EntityFactory::SceneToEntityHierachy(scene4, entity4);
			entity4->setTransform(Transform(glm::vec3(4, 0, 0), glm::vec3(5, 5, 5)));
		}
	}
};

//This is the entry point of the library
Application* Application::CreateApplication()
{
	return new Game();
}