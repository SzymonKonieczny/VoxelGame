#include "Shader.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include<fstream>
#include<sstream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		std::string vertexSrc = get_file_contents(vertexPath.c_str());
		std::string fragmentSrc = get_file_contents(fragmentPath.c_str());

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

std::string Shader::get_file_contents(const char* filename)
{
	

	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return "";
	}

	std::string content((std::istreambuf_iterator<char>(file)),
		(std::istreambuf_iterator<char>()));

	file.close();

	return content;
}

void Shader::AddUniform(std::string name, UniformType type)
{
	UniformData.insert( std::make_pair(name, Uniform(type, name) ));
}

void Shader::UploadAllUniforms()
{
	for (auto& uniform : UniformData)
	{
//#ifdef DEBUG
//		//if (!uniform.second.dataInitialized) std::cout << "DebugInfo: Uniform " << uniform.second.name << " was nerver assigned";
//#endif // DEBUG

		auto& data = UniformData[uniform.second.name].data;
		switch (uniform.second.type)
		{

		case UniformType::Float:
			UploadUniformFloat(uniform.second.name, data.Float1);
			break;
		case UniformType::Float2:
			UploadUniformFloat2(uniform.second.name, data.Float2);

			break;
		case UniformType::Float3:
			UploadUniformFloat3(uniform.second.name, data.Float3);

			break;
		case UniformType::Float4:
			UploadUniformFloat4(uniform.second.name, data.Float4);

			break;
		case UniformType::Mat4:
			UploadUniformMat4(uniform.second.name, data.Mat4);

			break;
		default:
			std::cout << "Using a Uniform type for which uploading wasnt yet implemented. Uniform name :" << uniform.second.name <<"\n";

			break;
		}
	}
}

void Shader::updateUniform(std::string name, UniformDataUnion data)
{
	UniformData[name].data = data;
}

