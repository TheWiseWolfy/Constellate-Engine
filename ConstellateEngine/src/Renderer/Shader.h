#pragma once
#include <string>
#include "glad/glad.h"

namespace csl {

	class Shader
	{
	private:
		GLuint _shaderID = 0;

	public:
		// the program ID
		// constructor reads and builds the shader
		Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath = "");
		~Shader();

		void Bind();
		void Unbind();

		// utility uniform functions
		GLuint GetUniform(const std::string uniformName) { 
			return glGetUniformLocation(_shaderID, uniformName.c_str() );
		}
	};

}