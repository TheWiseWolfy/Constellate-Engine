#include "RendererCommand.h"

#include "OpenGLRenderer/OpenGLRenderer.h"
#include "Renderer/Shader.h"
#include "Renderer/RenderBuffer.h"

csl::RendererCommand::RendererCommand()
{
	currentRenderer.reset(new OpenGLRenderer);
}

void csl::RendererCommand::DrawGame()
{
	
}
