#pragma once


namespace csl {
	class VertexBuffer {
	private:

	public:
		virtual ~VertexBuffer(){}

		virtual void Bind() = 0;
		virtual void Unbind() = 0;


		static VertexBuffer* VertexBufferOf(float* vertices, size_t size);
	};

	class IndexBuffer {
	private:
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static IndexBuffer* IndexBufferOf(unsigned int* vertices, size_t size);
	};

}