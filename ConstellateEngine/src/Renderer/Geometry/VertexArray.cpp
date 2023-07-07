/*
File: VertexArray.cpp

The maid idea behind the Create fuction is to return the VertexArray implementation coresponding to the
API currently in use. Because only 1 API is supported for now, it's a simple retun new.
*/

#include "VertexArray.h"

#include "Renderer/OpenGLRenderer/Geometry/OpenGLVertexArray.h"

namespace csl {

	VertexArray* VertexArray::Create()
	{
		return new OpenGLVertexArray();
	}
}