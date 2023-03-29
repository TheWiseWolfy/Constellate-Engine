#pragma once

#include "cslpch.h"
#include "Layout/BufferLayout.h"

namespace csl {


	class VertexBuffer {
	private:

	public:
		virtual ~VertexBuffer(){}

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout GetLayout() = 0;

		static VertexBuffer* VertexBufferOf(float* vertices, size_t size);
	};

	class IndexBuffer {
	private:
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual unsigned int GetCount() const = 0;


		static IndexBuffer* IndexBufferOf(unsigned int* vertices, size_t size);
	};

}