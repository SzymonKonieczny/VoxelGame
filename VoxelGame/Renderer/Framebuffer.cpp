#include "Framebuffer.h"
#include <glad/glad.h>
#include <iostream>
Framebuffer::Framebuffer(FramebufferOptions options) : Options(options)
{
	glGenFramebuffers(1, &m_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

	glGenTextures(1, &ColorTex);
	glBindTexture(GL_TEXTURE_2D, ColorTex);

	glTextureStorage2D(ColorTex, 1, GL_RGB, Options.Width, Options.Height);

	glTextureParameteri(ColorTex, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(ColorTex, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glGenTextures(1, &DepthStencilTex);
	glBindTexture(GL_TEXTURE_2D, DepthStencilTex);

	glTextureStorage2D(DepthStencilTex, 1, GL_DEPTH24_STENCIL8, Options.Width, Options.Height);

	glTextureParameteri(DepthStencilTex, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(DepthStencilTex, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_ID);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColorTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, DepthStencilTex, 0);


	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
}

