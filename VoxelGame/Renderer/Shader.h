#pragma once
#include <string>
#include <glad/glad.h>
#include <vector>
class Shader {
public:
	Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
	void Bind();
	void Unbind();

private:
	unsigned int m_ID;


};