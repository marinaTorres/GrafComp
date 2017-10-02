#pragma once
#include <GL/glew.h>
#include <string>

using namespace std;

class Shader {
public:
	Shader();
	~Shader();

	void CreateShader(string path, GLenum type);
	GLuint getHandle();
private:
	GLuint _shaderHandle;
};