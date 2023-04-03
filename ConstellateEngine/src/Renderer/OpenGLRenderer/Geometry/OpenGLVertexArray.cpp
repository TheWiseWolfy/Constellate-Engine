#include "OpenGLVertexArray.h"



namespace csl {
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &_vertexArrayId);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &_vertexArrayId);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(_vertexArrayId);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{

		glBindVertexArray(_vertexArrayId);
		vertexBuffer->Bind();

		uint32_t index = 0;
		BufferLayout layout = vertexBuffer->GetLayout();
		for (BufferElement element : layout.GetElements())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				StandardTypeToOpenGLType(element._type),
				element._normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element._offset);

			index++;
		}

		_vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(_vertexArrayId);
		indexBuffer->Bind();

		_indexBuffer = indexBuffer;
	}

}