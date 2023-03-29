#include "OpenGLRenderer.h"

#include "cslpch.h"
#include "glad/glad.h"

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