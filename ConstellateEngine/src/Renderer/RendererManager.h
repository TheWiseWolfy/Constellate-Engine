#pragma once

#include "cslpch.h"

#include "OpenGLRenderer/OpenGLRenderer.h"
#include "Shader.h"
#include "Geometry/VertexArray.h"
#include "Camera.h"

#include "Entity-Component/Components/GraphicsComponent.h"


namespace csl {

	class ColliderComponent;
	//This is the class that will interact with the currently loaded RendererAPI and 
	//manage the drawing queue and other API agnosting things
	class RendererManager {
	private:
		std::unique_ptr<IRenderer> _currentRenderer;
		unsigned int _VertexArray;

		std::unique_ptr<Camera> _camera;
	public:
		RendererManager();


		void DrawGame();
		void RenderCollider(ColliderComponent* colliderComponent);
		void SetCameraPosition(glm::vec3 position);
		void SetCameraRotation(glm::vec2 rotation);
		glm::vec3 GetCameraPosition();

	private:
		glm::mat4 PerspectiveView(glm::mat4 model, std::unique_ptr<Camera>& camera);
	};

}