#pragma once

#include "cslpch.h"
#include "Renderer/Geometry/RenderBuffer.h"

namespace csl {
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