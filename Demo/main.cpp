#include <iostream>

#include <Constellate.h>
#include <Core/EntryPoint.h>

#include <iostream>
#include <random>
#include <chrono>

#include "FirstPersonCamera.h"
#include "PlayerComponent.h"
#include "TargetComponent.h"
#include "RotationComponent.h"

#include "MyGUILayer.h"

using namespace csl;

class Demo : public Application {
private: 

	bool _firstMouse = true;
	float _lastX = 0;
	float _lastY = 0;
	FPCamera _camera;

	int _points = 0;
	std::unique_ptr<MyGUILayer> _guiLayer;
	bool _locked = true;

	bool _gravity = true;
public:
	Demo() {
		ShaderLoader::getInstance().loadShader("shader1",
			"E:\\Projects\\Git\\Constellate-Engine\\Game\\Shaders\\shader1.vert",
			"E:\\Projects\\Git\\Constellate-Engine\\Game\\Shaders\\shader1.frag"
		);

		ShaderLoader::getInstance().loadShader("shader2",
			"E:\\Projects\\Git\\Constellate-Engine\\Game\\Shaders\\shader2.vert",
			"E:\\Projects\\Git\\Constellate-Engine\\Game\\Shaders\\shader2.frag",
			"E:\\Projects\\Git\\Constellate-Engine\\Game\\Shaders\\shader2.geom"
		);

		_guiLayer = std::make_unique<MyGUILayer>();
		PushLayer(_guiLayer.get());

		Application::GetInstance().GetRenderer().SetSkyColor({ 0.2f, 0.2f, 0.2f });

		TestFuction();
	}
	~Demo(){
		
	}

	void OnEventCallback(EngineEvent& e) override {

		EventDispatcher dispatcher(e);

		dispatcher.Dispach<MouseMovedEvent>(std::bind(&Demo::OnMouseMoved, this, std::placeholders::_1));
		dispatcher.Dispach<KeyPressedEvent>(std::bind(&Demo::OnKeyPressed, this, std::placeholders::_1));
		dispatcher.Dispach<TargetHitEvent>(std::bind(&Demo::OnTargetEvent, this, std::placeholders::_1));
	};

	bool OnTargetEvent(TargetHitEvent& e) {
		_points++;

		_guiLayer->SetPoints(_points);
		CSL_INFO("Current points {0}", _points);
		return true;
	}

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

		if (e.GetKeyCode() == CSL_KEY_N && e.GetAction() == CSL_PRESS) {
			_gravity = !_gravity;
			Application::GetInstance().GetPhysicsManager().setGravity(_gravity);
			
		}
		if (e.GetKeyCode() == CSL_KEY_M && e.GetAction() == CSL_PRESS) {
			_locked = !_locked;
		}

		if (e.GetKeyCode() == CSL_KEY_B && e.GetAction() == CSL_PRESS) {
			{
				Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
				const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\target.obj");
				int id = TextureImporter::loadImageFromFile("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\Cylinder.001.png");

				EntityFactory::SceneToEntityHierachy(scene, entity, false, "shader1", id);


				//const aiScene* sceneCube = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\cube.obj");
				entity->addComponent<SphereCollider>(1.f);
				entity->addComponent<PhysicsComponent>();

				entity->addComponent<TargetComponent>();

				entity->SetPosition(glm::vec3(7, 1, -5.8));
			}
		}

		if (e.GetKeyCode() == CSL_KEY_C && e.GetAction() == CSL_PRESS) {
			{
				Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
				const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\sphere.obj");
				EntityFactory::SceneToEntityHierachy(scene, entity);

				entity->addComponent<SphereCollider>(0.2f);
				PhysicsComponent& phycomp = entity->addComponent<PhysicsComponent>();
				entity->addComponent<PlayerComponent>(_camera);
				entity->addTag("Projectile");

				phycomp.applyForce(_camera.getCameraDirection() * 1.5f);

				entity->SetPosition(poz);
				entity->SetScale({ 0.2f ,0.2f ,0.2f });
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

		if(_locked){
			Application::GetInstance().GetRenderer().SetCameraRotation(_camera.getYaw(), _camera.getPitch());
			//The mouse gets stuck in the middle of the window to accomoate the camera.
			Application::GetInstance().GetWindow().SetMousePosition(windowWidth / 2, windowHeight / 2);
		}
		return true;
	}

	void TestFuction() {

		{
			Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
			const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\floor.obj");
			EntityFactory::SceneToEntityHierachy(scene, entity);
			//const aiScene* sceneCube = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\cube.obj");
			entity->addComponent<PlaneColider>();
			auto& physics = entity->addComponent<PhysicsComponent>();
			physics.setStatic(true);
			entity->SetPosition(glm::vec3(0, -3, 0));
			entity->SetRotation({ 0.0f, 0.0f, 0.0f });

			//entity->addComponent<TargetComponent>();
		}
		int offset = -10;
		{
			Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
			const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\trueHidrant.obj");
			EntityFactory::SceneToEntityHierachy(scene, entity);
			entity->SetPosition( glm::vec3(offset, -2.5, -10) );
			entity->SetScale(glm::vec3(2, 2, 2) );
		}
		offset += 5;
		{
			Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
			const aiScene* scene3 = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\13466_Canaan_Dog_v1_L3.obj");
			entity->addComponent<RotationComponent>();
			entity->SetPosition(glm::vec3(offset, -3, -10));
			entity->SetRotation({ -3.14 / 2,0, 0 });  // xx zz yy
			entity->SetScale({ 0.1,0.1, 0.1 });  // xx zz yy
			EntityFactory::SceneToEntityHierachy(scene3, entity);
		}
		offset += 5;

		{
			Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
			const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\13466_Canaan_Dog_v1_L3.obj");
			entity->SetPosition(glm::vec3(offset, -3, -10));
			entity->SetRotation({ -3.14 / 2,0, 0 });  // xx zz yy
			entity->SetScale({ 0.05,0.05, 0.05 });  // xx zz yy
			EntityFactory::SceneToEntityHierachy(scene, entity);
		}
		offset += 5;

		{
			Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
			const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\Stone.obj");
			int id = TextureImporter::loadImageFromFile("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\test.png");

			EntityFactory::SceneToEntityHierachy(scene, entity, false, "shader1", id);
			entity->SetScale({ 0.2,0.2, 0.2 });  // xx zz yy

			entity->SetPosition(glm::vec3(offset, -3, -10));
		}

		offset += 5;

		{
			Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
			const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\Stone.obj");
			int id = TextureImporter::loadImageFromFile("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\diffuso.png");

			EntityFactory::SceneToEntityHierachy(scene, entity, false, "shader1", id);
			entity->SetScale({ 0.2,0.2, 0.2 });  // xx zz yy

			entity->SetPosition(glm::vec3(offset, -3, -10));
		}
		offset += 5;

		{
			Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
			const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\trueHidrant.obj");
			EntityFactory::SceneToEntityHierachy(scene, entity, false, "shader2");
			entity->SetPosition(glm::vec3(offset, -2.5, -10));
			entity->SetScale(glm::vec3(2, 2, 2));
		}
		offset += 5;
		//Ball tower
		{
			Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
			const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\sphere.obj");
			EntityFactory::SceneToEntityHierachy(scene, entity);

			entity->addComponent<SphereCollider>(1.0f);
			PhysicsComponent& phycomp = entity->addComponent<PhysicsComponent>();

			entity->SetPosition(glm::vec3(offset, 2.5, -10));
			entity->SetScale({ 1.0f ,1.0f ,1.0f });
		}
		{
			Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
			const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\sphere.obj");
			EntityFactory::SceneToEntityHierachy(scene, entity);

			entity->addComponent<SphereCollider>(0.8f);
			PhysicsComponent& phycomp = entity->addComponent<PhysicsComponent>();

			entity->SetPosition(glm::vec3(offset, 5.5, -10));
			entity->SetScale({ 0.8f ,0.8f ,0.8f });
		}
		{
			Entity* entity = Application::GetInstance().GetEntityManager().addEntity();
			const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\sphere.obj");
			EntityFactory::SceneToEntityHierachy(scene, entity);

			entity->addComponent<SphereCollider>(0.6f);
			PhysicsComponent& phycomp = entity->addComponent<PhysicsComponent>();

			entity->SetPosition(glm::vec3(offset, 7.5, -10));
			entity->SetScale({ 0.6f ,0.6f ,0.6f });
		}
	
		offset += 5;
		{
			Entity* entity = Application::GetInstance().GetEntityManager().addEntity();

			entity->addComponent<SphereCollider>(1.f);
			auto& phy = entity->addComponent<PhysicsComponent>();
			phy.setStatic(true);
			//here entity->addComponent<RendererComponent>() is called

			const aiScene* scene = AssetImporter::LoadModel("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\target.obj");
			int id = TextureImporter::loadImageFromFile("E:\\Projects\\Git\\Constellate-Engine\\Game\\Assets\\Cylinder.001.png");

			EntityFactory::SceneToEntityHierachy(scene, entity, false, "shader1", id);
			entity->addComponent<TargetComponent>();

			entity->SetPosition(glm::vec3(offset, 1.0, -10));
		}
	}
};

//This is the entry point of the library
Application* Application::CreateApplication()
{
	return new Demo();
}