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
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		void Bind();
		void Unbind();

		// utility uniform functions
		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
	};

}