#pragma once
#include <string>
#include <glad/glad.h>
#include <vector>
#include <map>
#include <glm/glm.hpp>
enum class UniformType {
	Float,Float2,Float3,Float4,Mat4
};
union UniformDataUnion {
	float Float1;
	glm::vec2 Float2;
	glm::vec3 Float3;
	glm::vec4 Float4;
	glm::mat4 Mat4;
	UniformDataUnion() {};
	UniformDataUnion(float a) :Float1(a) {};
	UniformDataUnion(glm::vec2 a) :Float2(a) {};
	UniformDataUnion(glm::vec3 a) :Float3(a) {};
	UniformDataUnion(glm::vec4 a) :Float4(a) {};
	UniformDataUnion(glm::mat4 a) :Mat4(a) {};
};
struct Uniform {
	UniformType type;
	std::string name;
	UniformDataUnion data;
	bool dataInitialized = false;
	Uniform(UniformType Type, std::string Name ) :
		type(Type), name(Name) {
		data.Mat4 = glm::mat4();
	}
	Uniform() {}
};
class Shader {
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	void Bind();
	void Unbind();
	unsigned int GetUniformLocation(std::string Name);
	void AddUniform(std::string name, UniformType type);
	void UploadAllUniforms();
	void updateUniform(std::string name, UniformDataUnion data);
	std::map<std::string, Uniform>& GetUniformData() { return UniformData; }

private:
	void UploadUniformMat4(std::string name, glm::mat4& value);
	void UploadUniformFloat(std::string name, float value);
	void UploadUniformFloat2(std::string name, glm::vec2& value);
	void UploadUniformFloat3(std::string name, glm::vec3& value);
	void UploadUniformFloat4(std::string name, glm::vec4& value);
	std::map<std::string, Uniform> UniformData;
	unsigned int m_ID;
	std::string get_file_contents(const char* filename);
	

};