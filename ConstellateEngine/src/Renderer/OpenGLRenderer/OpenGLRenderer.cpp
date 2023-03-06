#include "OpenGLRenderer.h"

#include "cslpch.h"
#include "glad/glad.h"

#include "Renderer/VertexArray.h"

namespace csl {

	void OpenGLRenderer::DrawElement(const std::shared_ptr<VertexArray>& _vertexArray)
	{
		glDrawElements(GL_TRIANGLES, _vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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
		glClear(GL_COLOR_BUFFER_BIT);
	}

}