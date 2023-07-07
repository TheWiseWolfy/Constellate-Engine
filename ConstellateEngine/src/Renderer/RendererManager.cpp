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
		_currentRenderer->SetSkyColor(_color);

		std::vector<std::unique_ptr<Entity>>& entities = Application::GetInstance().GetEntityManager().GetEntityVector();
		std::vector<GraphicsComponent*> graphicsComponents;

		for (auto& entity : entities) {
			if (entity->HasComponent(ComponentType::GraphicsComponentType)) {
				graphicsComponents.push_back((GraphicsComponent*)entity->GetComponent(ComponentType::GraphicsComponentType));
			}
			aux(entity,graphicsComponents);
		}

		for (auto&& component : graphicsComponents) {


			auto& shader = ShaderLoader::getInstance().getShader( component->getShader() );
			shader.Bind();

			//if (component->isWireframe()) {
			//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			//}
			//else {
			//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			//}

			glm::mat4 model;
			glm::mat4 perspective;

			//Calculating the model
			model = glm::mat4(1.0f);
			model = glm::translate(model, component->getEntity()->getAbsolutePosition() );
			auto scale = component->getEntity()->getAbsoluteScale();
			model = glm::scale(model, scale);
			glm::vec3 rotation = component->getEntity()->getAbsoluteRotation();
			model = glm::rotate(model, rotation.x , glm::vec3(1, 0, 0) ) ;
			model = glm::rotate(model, rotation.y , glm::vec3(0, 1, 0));
			model = glm::rotate(model, rotation.z , glm::vec3(0, 0, 1));
			

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
			{
				GLuint uniformID = shader.GetUniform("isTextured");
				glUniform1i(uniformID, (int)component->IsTextured());


				if (component->IsTextured()) {

					GLuint myTextureSamplerLocation = shader.GetUniform("myTextureSampler");

					GLuint textureUnit = 0; // Choose the texture unit you want to use
					glActiveTexture(GL_TEXTURE0 + textureUnit); // Activate the texture unit
					glBindTexture(GL_TEXTURE_2D, component->GetTextureID()); // Bind the texture to the active texture unit

					glUniform1i(myTextureSamplerLocation, textureUnit);
				}
			}
			_currentRenderer->DrawElement( component->GetVertexArray() );
		}
		
	}
	
	//Helper fuction
	//void RendererManager::RenderCollider(ColliderComponent* colliderComponent) {
	//	auto& shader = ShaderLoader::getInstance().getShader("shader2");
	//	shader.Bind();
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//	glm::mat4 model;
	//	model = glm::mat4(1.0f);

	//	glm::mat4 perspective;
	//	perspective = PerspectiveView(model, _camera);

	//
	//	{
	//		perspective = PerspectiveView(model, _camera);
	//		GLuint uniformID = shader.GetUniform("modelViewProjectionMatrix");
	//		glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(perspective));
	//	}
	//	{
	//		glm::mat4 normalMatrix = glm::transpose(glm::inverse(model));
	//		GLuint uniformID = shader.GetUniform("normalMatrix");
	//		glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	//	}
	//	{
	//		glm::vec3 cemeraVector = _camera->GetPostion();
	//		GLuint uniformID = shader.GetUniform("cameraPoz");
	//		glUniform3fv(uniformID, 1, glm::value_ptr(cemeraVector));
	//	}
	//		
	//	for (const Triangle& triangle : colliderComponent->GetTriangles()) {
	//		_currentRenderer->DrawTriangle(triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]);
	//	}
	//}
	void RendererManager::SetSkyColor(glm::vec3 color) {
		_color = color;
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
	void RendererManager::SetCameraRotation(float yaw, float pitch)
	{
		_camera->SetRotation(yaw, pitch);
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