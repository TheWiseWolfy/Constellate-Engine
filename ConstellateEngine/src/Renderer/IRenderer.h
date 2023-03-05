#pragma once


namespace csl {

	enum class API {
		None = 0,
		OpenGL = 1
	};

	class IRenderer {


		virtual void Clear() = 0;
		virtual void SetClearColor() = 0;


		virtual void DrawElement() = 0;

		virtual API GetAPI() = 0;
	};

}