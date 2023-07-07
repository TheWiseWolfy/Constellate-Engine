
#include "OpenGLIndexBuffer.h"
#include "cslpch.h"
#include <glad/glad.h>

namespace csl {

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, size_t size) : _count(size)
	{
		glGenBuffers(1, &_bufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		//void* dataPtr = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY);

		//if (dataPtr != nullptr)
		//{
		//	// Copy the indices data to the buffer
		//	for (size_t i = 0; i < size; i++)
		//	{
		//		_indicesCopy.push_back(( (unsigned int*)dataPtr)[i]);
		//	}

		//	// Unmap the buffer
		//	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		//}
		//glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

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