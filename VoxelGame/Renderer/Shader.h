#pragma once
#include <string>
#include <glad/glad.h>
#include <vector>
#include <map>
#include <glm/glm.hpp>
enum class UniformType {
	Float,Float2,Float3,Float4,Mat4
};
class Shader {
public:
	Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
	void Bind();
	void Unbind();
	unsigned int GetUniformLocation(std::string Name);
	void UploadUniformMat4(std::string name, glm::mat4& value);
	void UploadUniformFloat(std::string name, float value);
	void UploadUniformFloat2(std::string name, glm::vec2& value);
	void UploadUniformFloat3(std::string name, glm::vec3& value);
	void UploadUniformFloat4(std::string name, glm::vec4& value);

private:
	//std::map<std::string, std::pair<UniformType, GLuint>> 
	unsigned int m_ID;


};