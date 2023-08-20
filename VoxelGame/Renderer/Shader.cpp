#include "Shader.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
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

unsigned int Shader::GetUniformLocation(std::string Name)
{
	return glGetUniformLocation(m_ID, Name.c_str());
}

void Shader::UploadUniformMat4(std::string name, glm::mat4& value)
{
	GLuint loc = GetUniformLocation(name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));

}

void Shader::UploadUniformFloat(std::string name, float value)
{
	GLuint loc = GetUniformLocation(name);
	glUniform1f(loc, value);
}

void Shader::UploadUniformFloat2(std::string name, glm::vec2& value)
{
	GLuint loc = GetUniformLocation(name);
	glUniform2f(loc, value.x, value.y);
}

void Shader::UploadUniformFloat3(std::string name, glm::vec3& value)
{
	GLuint loc = GetUniformLocation(name);
	glUniform3f(loc, value.x, value.y, value.z);
}

void Shader::UploadUniformFloat4(std::string name, glm::vec4& value)
{
	GLuint loc = GetUniformLocation(name);
	glUniform4f(loc, value.x, value.y, value.z, value.w);
}
