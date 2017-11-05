#pragma once

#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include <IL/il.h>

using namespace glm;
using namespace std;

class Texture2D{
public:
	Texture2D();
	~Texture2D();
	
	void LoadTexture(string path);
	void Bind();
	void Unbind();

private:
	GLuint _textureId;
};