#pragma once

#include "Renderer/IRenderer.h"

namespace csl {


	class OpenGLRenderer : public IRenderer {

		virtual void DrawElement(const std::shared_ptr<VertexArray>& _vertexArray) override;

		virtual API GetAPI() override;

		virtual void Clear() override;
		virtual void SetClearColor() override;
	};





}