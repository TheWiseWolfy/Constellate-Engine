#pragma once

#include "cslpch.h"
#include "Renderer/RenderBuffer.h"

namespace csl {



	class OpenGLVertexBuffer : public VertexBuffer 
	{
	private:
		unsigned int _bufferID;
		BufferLayout _bufferLayout;
	public:
		OpenGLVertexBuffer(float* vertices, size_t size);
		virtual ~OpenGLVertexBuffer() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void SetLayout(const BufferLayout& layout) {
			_bufferLayout = layout;
		}
		virtual const BufferLayout GetLayout() override {
			return _bufferLayout;
		}
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	private:
		unsigned int _bufferID;
		unsigned int _count;

	public:
		OpenGLIndexBuffer(unsigned int* indices, size_t size);
		virtual ~OpenGLIndexBuffer() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual unsigned int GetCount() const override { return _count; }

	};

}