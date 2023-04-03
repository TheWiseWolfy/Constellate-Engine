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
				layout(location = 1) in vec3 a_Normals;
				layout(location = 2) in vec4 a_Color;

				out vec3 v_Position;
				out vec3 v_Normal;
				out vec4 v_Color;

				uniform mat4 modelViewProjectionMatrix;
				uniform mat4 normalMatrix;

				void main()
				{
					v_Position = a_Position;
					//v_Normal = a_Normals;
					v_Normal = (normalMatrix * vec4( a_Normals, 1.0)).xyz;
					v_Color = a_Color;
					gl_Position = modelViewProjectionMatrix * vec4(a_Position, 1.0);
	
				}
			)";

		std::string fragmentShader = R"(
				#version 330 core
			
				out vec4 color;

				in vec3 v_Position;
				in vec3 v_Normal;
				in vec4 v_Color;

				uniform vec3 cameraPoz;

				vec3 lighting(vec3 pos, vec3 normal, vec3 lightPos, vec3 viewPos, vec3 ambient, vec3 diffuse, vec3 specular, float specPower);

				void main()
				{
					vec3 ambient = vec3(0.9);
					vec3 diffuse = vec3(2, 2, 2);
					vec3 specular = vec3(0.8);
					float specPower = 32;

					vec3 lightPos = vec3(2, 3, 6);
					
					vec3 lightColor = lighting(v_Position, v_Normal, lightPos, cameraPoz, ambient, diffuse, specular, specPower);
					color =v_Color * vec4(lightColor, 1.0);
				}

				vec3 lighting(vec3 pos, vec3 normal, vec3 lightPos, vec3 viewPos, vec3 ambient, vec3 diffuse, vec3 specular, float specPower)
				{
					//Difuse lighting
					vec3 L = normalize(lightPos - pos );
					vec3 N = normalize(normal);
					float difusePower = 0;
	
					if( dot( L, N) > 0){
						difusePower = dot( L, N);
					}

					//Specular lighing
					vec3 V = normalize(viewPos - pos);
					vec3 R = reflect(-L, N);

					float spec = 0;
					float cosThetaSpec = dot( R, V);

					if( cosThetaSpec > 0){
						spec = pow(cosThetaSpec, specPower);
					} 

				//	vec3 final = ambient + diffuse * difusePower + spec * specPower ;
					vec3 final = ambient + diffuse * difusePower + spec * specPower;

					return final;
				}

			)";
		_shader = std::make_unique<Shader>(vertexSource, fragmentShader);
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
		_shader->Bind();

		
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

//			auto scale = component->getEntity()->getAbsoluteRotation();
			/*model = glm::rotate(model, 20.f, glm::vec3(1, 0, 0) ) ;
			model = glm::rotate(model, 20.f, glm::vec3(0, 1, 0));
			model = glm::rotate(model, 20.f, glm::vec3(0, 0, 1));*/

			perspective = PerspectiveView(model, _camera);

			GLuint uniformID = _shader->GetUniform("modelViewProjectionMatrix");
			glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(perspective));

			glm::mat4 normalMatrix = glm::transpose(glm::inverse(model));
			uniformID = _shader->GetUniform("normalMatrix");
			glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(normalMatrix));

			glm::vec3 cemeraVector = _camera->GetPostion();
			uniformID = _shader->GetUniform("cameraPoz");
			glUniform3fv(uniformID, 1, glm::value_ptr(cemeraVector));

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