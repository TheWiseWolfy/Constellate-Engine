#include "Shader.h"

#include "Core/Log.h"
#include "cslpch.h"

#include <iostream>

namespace csl {
	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertexPath.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			CSL_CORE_ERROR("Vertex shader compilation error !");
			CSL_CORE_ERROR(infoLog.data());
			return;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentPath.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			CSL_CORE_ERROR("Fragment shader compilation error !");
			CSL_CORE_ERROR(infoLog.data());
			return;
		}

	
		GLuint program = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader); 

			CSL_CORE_ERROR("Shader program linking error !");
			CSL_CORE_ERROR(infoLog.data());
			return;
		}

		_shaderID = program;

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	Shader::~Shader() {
		glDeleteProgram(_shaderID);
	}

	void Shader::Bind()
	{
		glUseProgram(_shaderID);
	}
	void Shader::Unbind()
	{
		glUseProgram(0);
	}

}