#include "Framebuffer.h"
#include <glad/glad.h>
#include <iostream>
Framebuffer::Framebuffer(FramebufferOptions options) : Options(options)
{
	glGenFramebuffers(1, &m_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

	if (options.ColorAttachment)
	{
	glGenTextures(1, &ColorTex);
	glBindTexture(GL_TEXTURE_2D, ColorTex);

	//glTextureStorage2D(ColorTex, 1, GL_RGB, Options.Width, Options.Height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Options.Width, Options.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	}
	else {
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}
	if (options.DepthStencilAttachment)
	{
	glGenTextures(1, &DepthStencilTex);
	glBindTexture(GL_TEXTURE_2D, DepthStencilTex);

	//glTextureStorage2D(DepthStencilTex, 1, GL_DEPTH24_STENCIL8, Options.Width, Options.Height);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		Options.Width, Options.Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	}
	else std::cout << "ERROR::FRAMEBUFFER:: Framebuffer without depth attachments is not implemented!" << std::endl;

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_ID);
	if (options.ColorAttachment) glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColorTex, 0);
	if (options.DepthStencilAttachment) glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthStencilTex, 0);


	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

}

void Framebuffer::BindColorTexture()
{
	glBindTexture(GL_TEXTURE_2D, ColorTex); //bind the current txt2d

}

void Framebuffer::BindDepthTexture()
{
	glBindTexture(GL_TEXTURE_2D, DepthStencilTex); //bind the current txt2d

}

