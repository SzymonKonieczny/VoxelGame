#pragma once
#include "Texture.h"
struct FramebufferOptions {
	unsigned int Width, Height;
//	GLenum Attachments;
};

class Framebuffer {
public:
	Framebuffer(FramebufferOptions options);

	void SetFramebufferOptions();
	void Bind();

	FramebufferOptions GetFramebufferOptions() { return Options; }
private:
	unsigned int ColorTex;
	unsigned int DepthStencilTex;
	FramebufferOptions Options;
	unsigned int m_ID;
};