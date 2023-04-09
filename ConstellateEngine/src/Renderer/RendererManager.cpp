#include "RendererManager.h"

#include "glm/glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "OpenGLRenderer/OpenGLRenderer.h"

#include "Renderer/Shader.h"
#include "Renderer/Geometry/RenderBuffer.h"


#include "Resources/AssetImporter.h"
#include "Resources/ShaderLoader.h"

#include "Core/Application.h"

namespace csl {


	RendererManager::RendererManager()
	{
		_currentRenderer = std::make_unique<OpenGLRenderer>();
		{
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 1.0f);
			glm::vec3  up = glm::vec3(0.0f, 1.0f, 0.0f);
			float yaw = -50.0f;
			float pitch = 0.0f;

			_camera = std::make_unique<Camera>(position, up, yaw, pitch);
		}

		ShaderLoader::getInstance().loadShader("shader1",
			"E:\\Projects\\Git\\Constellate-Engine\\Game\\Shaders\\shader1.vert",
			"E:\\Projects\\Git\\Constellate-Engine\\Game\\Shaders\\shader1.frag"
		);
	}

	//This is an ugly piece of code that sadly has to live on for now
	void aux(std::unique_ptr<Entity>& entity, std::vector<GraphicsComponent*>& graphicsComponents) {
		auto& childrenEntitys = entity->GetChildren();

		for (auto& entity : childrenEntitys) {
			if (entity->HasComponent(ComponentType::GraphicsComponentType)) {
				graphicsComponents.push_back((GraphicsComponent*)entity->GetComponent(ComponentType::GraphicsComponentType));
			}
			aux(entity, graphicsComponents);
		}

	}


	void RendererManager::DrawGame()
	{
		_currentRenderer->Clear();
		_currentRenderer->SetClearColor();

		auto& shader = ShaderLoader::getInstance().getShader("shader1");
		shader.Bind();
		//_shader->Bind();

		std::vector<std::unique_ptr<Entity>>& entities = Application::GetInstance().GetEntityManager().GetEntityVector();
		std::vector<GraphicsComponent*> graphicsComponents;

		for (auto& entity : entities) {
			if (entity->HasComponent(ComponentType::GraphicsComponentType)) {
				graphicsComponents.push_back((GraphicsComponent*)entity->GetComponent(ComponentType::GraphicsComponentType));
			}
			aux(entity,graphicsComponents);
		}


		for (auto&& component : graphicsComponents) {
			glm::mat4 model;
			glm::mat4 perspective;

			model = glm::mat4(1.0f);

			model = glm::translate(model, component->getEntity()->getAbsolutePosition() );

			auto scale = component->getEntity()->getAbsoluteScale();
			model = glm::scale(model, scale);

			/*
			auto rotation = component->getEntity()->getAbsoluteRotation();
			model = glm::rotate(model, 20.f, glm::vec3(1, 0, 0) ) ;
			model = glm::rotate(model, 20.f, glm::vec3(0, 1, 0));
			model = glm::rotate(model, 20.f, glm::vec3(0, 0, 1));
			*/

			{
			perspective = PerspectiveView(model, _camera);
			GLuint uniformID = shader.GetUniform("modelViewProjectionMatrix");
			glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(perspective));
			}
			{
			glm::mat4 normalMatrix = glm::transpose(glm::inverse(model));
			GLuint uniformID = shader.GetUniform("normalMatrix");
			glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(normalMatrix));
			}
			{
				glm::vec3 cemeraVector = _camera->GetPostion();
				GLuint uniformID = shader.GetUniform("cameraPoz");
				glUniform3fv(uniformID, 1, glm::value_ptr(cemeraVector));
			}

			_currentRenderer->DrawElement( component->GetVertexArray() );
		}
		
	}



	void RendererManager::SetCameraPosition(glm::vec3 position)
	{
		_camera->SetPosition(position);
	}

	glm::vec3 RendererManager::GetCameraPosition()
	{
		return _camera->GetPostion();
	}
	//GraphicsComponent& RendererController::AddGraphicsComponent(GraphicsComponent component)
	//{
	//	
	//}
	void RendererManager::SetCameraRotation(glm::vec2 rotation)
	{
		_camera->SetRotation(rotation);
	}

	glm::mat4  RendererManager::PerspectiveView(glm::mat4 model, std::unique_ptr<Camera>& camera) {
		glm::mat4 projectionMatrix;

		//Perspective Matrix
		projectionMatrix = glm::perspective(glm::pi<float>() / 2, 1.0f, 0.1f, 300.0f);

		//View Matrix
		glm::mat4 viewMatrix = camera->GetViewMatrix();

		glm::mat4 final = projectionMatrix *  viewMatrix * model  ;
		return final;
	}

}