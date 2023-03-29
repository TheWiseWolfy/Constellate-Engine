#pragma once

#include "cslpch.h"
#include "Renderer/Geometry/RenderBuffer.h"

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

	
}