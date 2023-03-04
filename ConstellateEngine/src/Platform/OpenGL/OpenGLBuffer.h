#pragma once

#include "Renderer/RenderBuffer.h"

namespace csl {

	class OpenGLVertexBuffer : public VertexBuffer 
	{
	private:
		unsigned int _bufferID;
	public:
		OpenGLVertexBuffer(float* vertices, size_t size);
		virtual ~OpenGLVertexBuffer() {}

		virtual void Bind() override;
		virtual void Unbind() override;


	};

	class OpenGLIndexBuffer : public IndexBuffer {
	private:
		unsigned int _bufferID;
	public:
		OpenGLIndexBuffer(unsigned int* indices, size_t size);
		virtual ~OpenGLIndexBuffer() {}

		virtual void Bind() override;
		virtual void Unbind() override;

	};

}