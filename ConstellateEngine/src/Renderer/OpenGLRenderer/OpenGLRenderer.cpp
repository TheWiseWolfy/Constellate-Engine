#include "OpenGLRenderer.h"

#include "cslpch.h"
#include "glad/glad.h"
#include "glm.hpp"

#include "Renderer/Geometry/VertexArray.h"

namespace csl {

	OpenGLRenderer::OpenGLRenderer() {
		glEnable(GL_DEPTH_TEST);
	}


	void OpenGLRenderer::DrawElement(const std::unique_ptr<VertexArray>& _vertexArray)
	{
		_vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, _vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

	}

	void OpenGLRenderer::DrawTriangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3)
	{
		float vertices[9] = { v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z };

		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 3, &vertices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDisableVertexAttribArray(0);
	}

	API OpenGLRenderer::GetAPI()
	{
		return API::OpenGL;
	}

	void OpenGLRenderer::SetClearColor()
	{
		glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
	}

	void OpenGLRenderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

}