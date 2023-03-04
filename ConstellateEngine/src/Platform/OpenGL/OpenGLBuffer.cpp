
#include "OpenGLBuffer.h"
#include "cslpch.h"
#include <glad/glad.h>

namespace csl {
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, size_t size)
	{
		glGenBuffers(1, &_bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &_bufferID);
	}

	void csl::OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
	}
	void OpenGLVertexBuffer::Unbind(){
	
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//__________________________________INDEX BUFFER______________
	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, size_t size)
	{
		glGenBuffers(1, &_bufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &_bufferID);
	}

	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferID);
	}
	void OpenGLIndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}