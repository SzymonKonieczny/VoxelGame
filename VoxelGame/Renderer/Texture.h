#pragma once
#include <string>
#include <glad/glad.h>
class Texture {
public:
	Texture(std::string path);


	void Bind(unsigned int slot = 0);
	void Unbind();

private:
	unsigned int m_ID;
	 char* DataBuffer;
	int m_Width, m_Height, m_BitsPerPixel;
	std::string Path;


};
