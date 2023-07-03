#pragma once

#include "Renderer/IRenderer.h"

namespace csl {


	class OpenGLRenderer : public IRenderer {
	private:
		glm::vec3 _color;
	public:
		OpenGLRenderer();

		virtual void DrawElement(const std::unique_ptr<VertexArray>& _vertexArray) override;
		virtual void DrawTriangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3) override;

		virtual API GetAPI() override;

		virtual void Clear() override;
		virtual void SetSkyColor(glm::vec3 color) override;

		virtual void SetClearColor() override;
	};





}