#include "RendererController.h"

#include "glm/glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


#include "OpenGLRenderer/OpenGLRenderer.h"
#include "Renderer/Shader.h"

#include "Renderer/Geometry/RenderBuffer.h"

namespace csl {


	RendererController::RendererController()
	{
		_currentRenderer = std::make_unique<OpenGLRenderer>();
		{
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 1.0f);
			glm::vec3  up = glm::vec3(0.0f, 1.0f, 0.0f);
			float yaw = -50.0f;
			float pitch = 0.0f;

			_camera = std::make_unique<Camera>(position, up, yaw, pitch);
		}


		//////////////////////////////////
		{
		std::unique_ptr<VertexArray> vertexArray(VertexArray::Create());

		float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f
		};
		unsigned int indices[3] = { 0, 1, 2 };

		std::unique_ptr<VertexBuffer> vertexBuffer(VertexBuffer::VertexBufferOf(vertices, sizeof(vertices)));
		std::unique_ptr<IndexBuffer> indexBuffer(IndexBuffer::IndexBufferOf(indices, sizeof(indices)));

		BufferLayout layout = {
			{ OpenGLDataType::Float3, "a_Position" },
			{ OpenGLDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);

		vertexArray->AddVertexBuffer(std::move(vertexBuffer));
		vertexArray->SetIndexBuffer(std::move(indexBuffer));

		glm::vec3 positionModel = glm::vec3(0, 0.3, 0.3);
		GraphicsComponent* wah = new GraphicsComponent(std::move(vertexArray), positionModel, glm::vec3(1, 1, 1));
		_componentList.emplace_back(std::move(wah));

		}
		//////////////////////////////////
		{
			std::unique_ptr<VertexArray> vertexArray(VertexArray::Create());

			float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f
			};
			unsigned int indices[3] = { 0, 1, 2 };

			std::unique_ptr<VertexBuffer> vertexBuffer(VertexBuffer::VertexBufferOf(vertices, sizeof(vertices)));
			std::unique_ptr<IndexBuffer> indexBuffer(IndexBuffer::IndexBufferOf(indices, sizeof(indices)));

			BufferLayout layout = {
				{ OpenGLDataType::Float3, "a_Position" },
				{ OpenGLDataType::Float4, "a_Color" }
			};
			vertexBuffer->SetLayout(layout);

			vertexArray->AddVertexBuffer(std::move(vertexBuffer));
			vertexArray->SetIndexBuffer(std::move(indexBuffer));

			glm::vec3 positionModel = glm::vec3(0, 0.9, 0.8);
			GraphicsComponent* wah = new GraphicsComponent(std::move(vertexArray), positionModel, glm::vec3(1, 1, 1));
			_componentList.emplace_back(std::move(wah));
		}
		//////////////////////////////////
	

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

	void RendererController::DrawGame()
	{
		_currentRenderer->Clear();
		_currentRenderer->SetClearColor();
		_shader->Bind();


		glm::mat4 model;

		for (auto&& component : _componentList) {
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

	void RendererController::SetCameraPosition(glm::vec3 position)
	{
		_camera->SetPosition(position);
	}

	glm::vec3 RendererController::GetCameraPosition()
	{
		return _camera->GetPostion();
	}
	//GraphicsComponent& RendererController::AddGraphicsComponent(GraphicsComponent component)
	//{
	//	
	//}
	void RendererController::SetCameraRotation(glm::vec2 rotation)
	{
		_camera->SetRotation(rotation);
	}

	glm::mat4  RendererController::PerspectiveView(glm::mat4 model, std::unique_ptr<Camera>& camera) {
		glm::mat4 projectionMatrix;

		//Perspective Matrix
		projectionMatrix = glm::perspective(glm::pi<float>() / 2, 1.0f, 0.1f, 300.0f);

		//View Matrix
		glm::mat4 viewMatrix = camera->GetViewMatrix();

		glm::mat4 final = projectionMatrix *  viewMatrix * model  ;
		return final;
	}

}