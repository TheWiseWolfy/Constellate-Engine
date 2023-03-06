#pragma once

#include "Renderer/VertexArray.h"


namespace csl {

	enum class API {
		None = 0,
		OpenGL = 1
	};

	class IRenderer {

	public:
		virtual void Clear() = 0;
		virtual void SetClearColor() = 0;

		virtual void DrawElement(const std::shared_ptr<VertexArray>& _vertexArray) = 0;

		virtual API GetAPI() = 0;
	};

}