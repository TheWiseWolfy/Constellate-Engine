#pragma once

#include "Renderer/IRenderer.h"

namespace csl {


	class OpenGLRenderer : public IRenderer {
	public:
		OpenGLRenderer();

		virtual void DrawElement(const std::unique_ptr<VertexArray>& _vertexArray) override;
		virtual void DrawTriangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3) override;

		virtual API GetAPI() override;

		virtual void Clear() override;
		virtual void SetClearColor() override;
	};





}