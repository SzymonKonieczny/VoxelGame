#include "Framebuffer.h"
#include <glad/glad.h>
Framebuffer::Framebuffer(FramebufferOptions options) : Options(options)
{
	glGenBuffers(1, &m_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);



}