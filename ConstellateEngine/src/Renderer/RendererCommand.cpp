#include "RendererCommand.h"

#include "OpenGLRenderer/OpenGLRenderer.h"
#include "Renderer/Shader.h"
#include "Renderer/RenderBuffer.h"

csl::RendererCommand::RendererCommand()
{
	currentRenderer.reset(new OpenGLRenderer);


	_vertexArray.reset(VertexArray::Create());

	float vertices[3 * 7] = {
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
	 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f
	};

	unsigned int indices[3] = { 0, 1, 2 };

	//_vertexBuffer = std::make_unique<VertexBuffer>W( VertexBuffer::VertexBufferOf(vertices, sizeof(vertices)));
	//_vertexBuffer->Bind();

	_vertexBuffer.reset(VertexBuffer::VertexBufferOf(vertices, sizeof(vertices)));
	_indexBuffer.reset(IndexBuffer::IndexBufferOf(indices, sizeof(indices)));

	BufferLayout layout = {
		{ OpenGLDataType::Float3, "a_Position" },
		{ OpenGLDataType::Float4, "a_Color" }
	};
	_vertexBuffer->SetLayout(layout);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	//glEnableVertexAttribArray(0);


	_vertexArray->AddVertexBuffer(_vertexBuffer);
	_vertexArray->SetIndexBuffer(_indexBuffer);

	std::string vertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
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

void csl::RendererCommand::DrawGame()
{
	_shader->Bind();
	glBindVertexArray(_VertexArray);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);


	
}
