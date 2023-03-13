#pragma once

#include "cslpch.h"
#include "Renderer/Geometry/RenderBuffer.h"
#include "Renderer/Geometry/VertexArray.h"

namespace csl {

	static GLenum StandardTypeToOpenGLType(OpenGLDataType type)
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

	class OpenGLVertexArray : public VertexArray
	{
	private:
		unsigned int _vertexArrayId;
		std::vector<std::shared_ptr<VertexBuffer>> _vertexBuffers;
		std::shared_ptr<IndexBuffer> _indexBuffer;
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return _vertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return _indexBuffer; }

	};

}