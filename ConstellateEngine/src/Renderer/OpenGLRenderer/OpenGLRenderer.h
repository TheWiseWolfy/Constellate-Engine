#pragma once

#include "Renderer/IRenderer.h"

namespace csl {


	class OpenGLRenderer : public IRenderer {
	public:
		OpenGLRenderer();

		virtual void DrawElement(const std::unique_ptr<VertexArray>& _vertexArray) override;

		virtual API GetAPI() override;

		virtual void Clear() override;
		virtual void SetClearColor() override;
	};





}