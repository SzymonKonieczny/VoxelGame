#pragma once
struct FramebufferOptions {
	unsigned int Width, Height;
};

class Framebuffer {
public:
	Framebuffer(FramebufferOptions options);

	void SetFramebufferOptions();

	FramebufferOptions GetFramebufferOptions() { return Options; }
private:
	FramebufferOptions Options;
	unsigned int m_ID;
};