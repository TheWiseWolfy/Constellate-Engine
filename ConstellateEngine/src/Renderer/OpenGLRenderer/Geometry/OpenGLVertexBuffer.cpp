
#include "OpenGLVertexBuffer.h"
#include "cslpch.h"
#include <glad/glad.h>

namespace csl {
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, size_t size)
	{
		glGenBuffers(1, &_bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, _bufferID);

		//This is the actual copying step, from now on, vertices can be deleted
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
}