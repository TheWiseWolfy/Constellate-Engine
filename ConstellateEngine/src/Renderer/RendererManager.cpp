#include "RendererManager.h"

#include "glm/glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "OpenGLRenderer/OpenGLRenderer.h"

#include "Renderer/Shader.h"
#include "Renderer/Geometry/RenderBuffer.h"


#include "Resources/AssetImporter.h"
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

		std::string vertexSource = R"(
				#version 330 core
			
				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				out vec3 v_Position;
				out vec4 v_Color;

				uniform mat4 modelViewProjectionMatrix;

				void main()
				{
					v_Position = a_Position;
					v_Color = a_Color;
					gl_Position = modelViewProjectionMatrix * vec4(a_Position, 1.0);
	
				}
			)";

		std::string fragmentShader = R"(
				#version 330 core
			
				layout(location = 0) out vec4 color;

				in vec3 v_Position;
				in vec4 v_Color;

				void main()
				{
					//color = vec4(v_Position * 0.5 + 0.5, 1.0);
					color = v_Color;
				}
			)";
		_shader = std::make_unique<Shader>(vertexSource, fragmentShader);
	}

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
		_shader->Bind();

		std::vector<std::unique_ptr<Entity>>& entities = Application::GetInstance().GetEntityManager().GetEntityVector();
		std::vector<GraphicsComponent*> graphicsComponents;
		for (auto& entity : entities) {
			if (entity->HasComponent(ComponentType::GraphicsComponentType)) {
				graphicsComponents.push_back((GraphicsComponent*)entity->GetComponent(ComponentType::GraphicsComponentType));
			}
			aux(entity,graphicsComponents);
		}


		glm::mat4 model;

		for (auto&& component : graphicsComponents) {
			//This has to be changed.
			model = glm::mat4(1.0f);
			model = glm::translate(model, component->GetPosition()  );
			model = glm::scale(model, component->GetScale() );
			model = PerspectiveView(model, _camera);

			GLuint uniformID = _shader->GetUniform("modelViewProjectionMatrix");
			glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(model));


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