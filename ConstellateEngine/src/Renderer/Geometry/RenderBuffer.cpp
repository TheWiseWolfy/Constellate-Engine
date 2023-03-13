#include "RenderBuffer.h"

#include "Renderer/OpenGLRenderer/OpenGLBuffer.h"

namespace csl {
	VertexBuffer* VertexBuffer::VertexBufferOf(float* vertices, size_t size)
	{
		return new OpenGLVertexBuffer(vertices, size);
	}

	IndexBuffer* IndexBuffer::IndexBufferOf(unsigned int* indices, size_t size)
	{
		return new OpenGLIndexBuffer(indices, size);
	}
}