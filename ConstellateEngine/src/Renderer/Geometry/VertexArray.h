#pragma once
#include <glad/glad.h>
#include "cslpch.h"

#include "RenderBuffer.h"

namespace csl {

	static GLenum StandardTypeToGlType(OpenGLDataType type)
	{
		using enum OpenGLDataType;
		switch (type)
		{
		case Float:    return GL_FLOAT;
		case Float2:   return GL_FLOAT;
		case Float3:   return GL_FLOAT;
		case Float4:   return GL_FLOAT;
		case Mat3:     return GL_FLOAT;
		case Mat4:     return GL_FLOAT;
		case Int:      return GL_INT;
		case Int2:     return GL_INT;
		case Int3:     return GL_INT;
		case Int4:     return GL_INT;
		case Bool:     return GL_BOOL;
		}

		return 0;
	}


	class VertexArray {
	private:
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};

}