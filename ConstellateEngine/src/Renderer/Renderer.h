#pragma once

namespace csl {

	enum class RendererAPI {
		None = 0,
		OpenGL = 1,
		DirectX = 2
	};

	class Renderer {

		static RendererAPI _rendererAPI;
	public:
		static RendererAPI getAPI() {
			return _rendererAPI;
		}
	};
}