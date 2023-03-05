#pragma once

#include "cslpch.h"

#include "OpenGLRenderer/OpenGLRenderer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Renderer/RenderBuffer.h"

namespace csl {

	//This is the class that will interact with the currently loaded RendererAPI and 
	//manage the drawing queue and other API agnosting things
	class RendererCommand {
	private:
		std::unique_ptr<IRenderer> currentRenderer;
		unsigned int _VertexArray;

		std::shared_ptr<VertexArray> _vertexArray;
		std::shared_ptr<Shader> _shader;
		std::shared_ptr<VertexBuffer> _vertexBuffer;
		std::shared_ptr<IndexBuffer>_indexBuffer;
	public:
		RendererCommand();

		void DrawGame();
	};

}