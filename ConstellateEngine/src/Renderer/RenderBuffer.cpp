#include "RenderBuffer.h"
#include "cslpch.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer/Renderer.h"

namespace csl {
	VertexBuffer* VertexBuffer::VertexBufferOf(float* vertices, size_t size)
	{
		switch ( Renderer::getAPI() )
		{
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		default:
			return nullptr;
			break;
		}
	}

	IndexBuffer* IndexBuffer::IndexBufferOf(unsigned int* indices, size_t size)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		default:
			return nullptr;
			break;
		}
	}


}