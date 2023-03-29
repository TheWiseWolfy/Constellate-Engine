
#include "OpenGLIndexBuffer.h"
#include "cslpch.h"
#include <glad/glad.h>

namespace csl {

	//__________________________________INDEX BUFFER______________
	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, size_t size) : _count(size)
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