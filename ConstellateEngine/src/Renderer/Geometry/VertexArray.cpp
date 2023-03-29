#include "VertexArray.h"

#include "Renderer/OpenGLRenderer/Geometry/OpenGLVertexArray.h"

namespace csl {

	VertexArray* VertexArray::Create()
	{
		return new OpenGLVertexArray();
	}
}