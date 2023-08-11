#include "Shader.h"
#include <iostream>
Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
{


		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);


	const char* Src =vertexSrc.c_str();
	glShaderSource(vertexShader, 1, &Src, 0);


	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		glDeleteShader(vertexShader);

		std::cout << "----- VERTEX SHADER ERROR ----- \n" << infoLog.data() << "\n";
		return;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	Src = fragmentSrc.c_str();
	glShaderSource(fragmentShader, 1, &Src, 0);

	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);
		std::cout << "----- FRAGMENT SHADER ERROR ----- \n" << infoLog.data() << "\n";


		return;
	}
	GLuint program = glCreateProgram();
	m_ID = program;

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(program);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		std::cout << "----- SHADER LINKING ERROR ----- \n" << infoLog.data() << "\n";

		return;
	}

	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
}

void Shader::Bind()
{
	glUseProgram(m_ID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}
