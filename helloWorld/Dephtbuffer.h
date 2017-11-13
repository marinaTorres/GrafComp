#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>


using namespace glm;
using namespace std;
class Dephtbuffer{
public:
	Dephtbuffer();
	~Dephtbuffer();
	
	void Create(int resolution);
	void Bind();
	void Unbind();
	void BindDepthMap();
	void UnbindDepthMap();
private:
	GLuint _framebuffer;
	GLuint _depthmap;
	GLuint _resolution;
};