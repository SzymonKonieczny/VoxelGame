#include "Texture.h"
#include "stb/stb_image.h"
#include <iostream>
Texture::Texture(std::string path)
	:Path(path), m_Width(0), m_Height(0), m_ID(0), m_BitsPerPixel(0), DataBuffer(nullptr)
{
	
	
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	stbi_set_flip_vertically_on_load(1);
	DataBuffer  = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BitsPerPixel, 4);

	glTextureStorage2D(m_ID, 1, GL_RGBA8, m_Width, m_Height);

	glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
						
	glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(m_ID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, DataBuffer);

	stbi_image_free(DataBuffer);
}

void Texture::Bind(unsigned int slot)
{
	glBindTextureUnit(slot,m_ID);
}

void Texture::Unbind()
{
}
