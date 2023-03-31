#pragma once

#include "cslpch.h"

#include "OpenGLRenderer/OpenGLRenderer.h"
#include "Shader.h"
#include "Geometry/VertexArray.h"
#include "Camera.h"
#include "Entity-Component/Components/GraphicsComponent.h"
#include "Entity-Component/Entity.h"


namespace csl {

	//This is the class that will interact with the currently loaded RendererAPI and 
	//manage the drawing queue and other API agnosting things
	class RendererManager {
	private:
		std::vector<std::unique_ptr<GraphicsComponent>> _componentList;

		std::unique_ptr<IRenderer> _currentRenderer;
		unsigned int _VertexArray;


		std::shared_ptr<Shader> _shader;
		//std::shared_ptr<VertexBuffer> _vertexBuffer;
		//std::shared_ptr<IndexBuffer>_indexBuffer;
		//std::shared_ptr<VertexArray> _vertexArray;

		std::unique_ptr<Camera> _camera;
	public:
		RendererManager();


		void DrawGame();
		void SetCameraPosition(glm::vec3 position);
		void SetCameraRotation(glm::vec2 rotation);
		glm::vec3 GetCameraPosition();

		//GraphicsComponent& AddGraphicsComponent(GraphicsComponent component);

	private:
		glm::mat4 PerspectiveView(glm::mat4 model, std::unique_ptr<Camera>& camera);
	};

}