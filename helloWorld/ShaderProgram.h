#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>
#include "Shader.h"
using namespace std;
using namespace glm;

class ShaderProgram {
public:
	ShaderProgram();
	~ShaderProgram();
	
	void CreateProgram();
	void AttachShader(string path, GLenum type);
	void LinkProgram();
	void Activate();
	void Deactivate();
	void SetAttribute(GLuint locationIndex, string name);
	void SetUniformf(string name, float value);
	void SetUniformI(string name, int value);
	void SetUniformf(string name, float x, float y);
	void SetUniformf(string name, float x, float y, float z);
	void SetUniformf(string name, float x, float y, float z, float w);
	void SetUniformMatrix(string name, mat4 matrix);
	void SetUniformMatrix3(string name, glm::mat3 matrix);


private:
	GLuint _programHandle;
	vector<unique_ptr<Shader>> _attachedShaders;

	void DeleteAndDetachShaders();
	void DeleteProgram();
};
