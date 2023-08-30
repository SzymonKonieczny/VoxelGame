#pragma once
#include "Texture.h"
struct FramebufferOptions {
	unsigned int Width, Height;
	bool ColorAttachment;
	bool DepthStencilAttachment;
	FramebufferOptions(unsigned int width, unsigned int height, bool useColorAttachment = true, bool useDepthStencilAttachment = true)
		: Width(width), Height(height), ColorAttachment(useColorAttachment), DepthStencilAttachment(useDepthStencilAttachment) {};
//	GLenum Attachments;
};

class Framebuffer {
public:
	Framebuffer(FramebufferOptions options);

	void SetFramebufferOptions();
	void Bind();
	void BindColorTexture();
	void BindDepthTexture();

	unsigned int getColorTex() { return ColorTex; }
	unsigned int getDepthStencilTex() { return DepthStencilTex; }

	FramebufferOptions GetFramebufferOptions() { return Options; }
private:
	unsigned int ColorTex=0;
	unsigned int DepthStencilTex=0;
	FramebufferOptions Options;
	unsigned int m_ID;
};