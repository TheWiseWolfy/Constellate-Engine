#pragma once

#include "Renderer/IRenderer.h"

namespace csl {


	class OpenGLRenderer : public IRenderer {


		virtual void Clear() override;
		virtual void SetClearColor() override;


		virtual void DrawElement() override;

		virtual API GetAPI() override;
	};





}