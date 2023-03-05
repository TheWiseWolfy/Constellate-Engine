#include "VertexArray.h"

#include "OpenGLRenderer/OpenGLVertexArray.h"

namespace csl {

	VertexArray* VertexArray::Create()
	{
		return new OpenGLVertexArray();
	}

}