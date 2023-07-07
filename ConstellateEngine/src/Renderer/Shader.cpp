#include "Shader.h"

#include "Core/Log.h"
#include "cslpch.h"

#include <iostream>

namespace csl {
	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
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

	
		GLuint geometryShader = 0;
		if (!geometryPath.empty())
		{
			geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* geometrySource = (const GLchar*)geometryPath.c_str();
			glShaderSource(geometryShader, 1, &geometrySource, 0);

			glCompileShader(geometryShader);

			glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(geometryShader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(geometryShader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(geometryShader);
				glDeleteShader(fragmentShader);
				glDeleteShader(vertexShader);

				CSL_CORE_ERROR("Geometry shader compilation error!");
				CSL_CORE_ERROR(infoLog.data());
				return;
			}
		}


		//Compile final program
		GLuint program = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		if (geometryShader != 0)
		{
			glAttachShader(program, geometryShader);
		}

		// Link our program
		glLinkProgram(program);


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
			if (geometryShader != 0)
			{
				glDeleteShader(geometryShader);
			}

			CSL_CORE_ERROR("Shader program linking error !");
			CSL_CORE_ERROR(infoLog.data());
			return;
		}

		_shaderID = program;

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
		if (geometryShader != 0)
		{
			glDetachShader(program, geometryShader);
		}

		//Delete the shaders now
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		if (geometryShader != 0)
		{
			glDeleteShader(geometryShader);
		}
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