#include "Dephtbuffer.h"

Dephtbuffer::Dephtbuffer(){
	_framebuffer = 0;
	_depthmap = 0;
	_resolution = 0;
}

Dephtbuffer::~Dephtbuffer(){
	glDeleteFramebuffers(1, &_framebuffer);
	glDeleteTextures(1, &_depthmap);
}

void Dephtbuffer::Create(int resolution) {
	_resolution = resolution;
	//OpenGL
	glGenFramebuffers(1, &_framebuffer);
	Bind();
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	glGenTextures(1, &_depthmap);
	BindDepthMap();
	//texture filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// y wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		resolution, resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		GL_TEXTURE_2D, _depthmap, 0);

	Unbind();
	
}

void Dephtbuffer::Bind(){
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
	glViewport(0, 0, _resolution, _resolution);
	
}

void Dephtbuffer::Unbind(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Dephtbuffer::BindDepthMap(){
	glBindTexture(GL_TEXTURE_2D, _depthmap);
}

void Dephtbuffer::UnbindDepthMap(){
	glBindTexture(GL_TEXTURE_2D, 0);
}
