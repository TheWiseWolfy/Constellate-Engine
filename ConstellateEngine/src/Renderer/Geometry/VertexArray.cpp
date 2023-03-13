#include "VertexArray.h"

#include "Renderer/OpenGLRenderer/OpenGLVertexArray.h"

namespace csl {

	VertexArray* VertexArray::Create()
	{
		return new OpenGLVertexArray();
	}

}