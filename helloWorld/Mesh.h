#pragma once

#include <GL/glew.h>
#include <vector>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Mesh {
public:
	Mesh();
	~Mesh();

	void CreateMesh(GLuint vertexCount);
	void Draw(GLenum primitive);
	void SetPositionAttribute(vector<vec2> positions, GLenum usage, GLuint locationIndex);
	void SetPositionAttribute(vector<vec3> positions, GLenum usage, GLuint locationIndex);
	void SetColorAttribute(vector<vec3> colors, GLenum usage, GLuint locationIndex);
	void SetColorAttribute(vector<vec4> colors, GLenum usage, GLuint locationIndex);
	void SetIndices(vector<unsigned int> indices, GLenum usage);

private:
	GLuint _vertexArrayObject;
	GLuint _positionsVertexBufferObject;
	GLuint _colorsVertexBufferObject;
	GLuint _vertexCount;

	GLuint _indicesBufferObject;
	GLint  _indicesCount;

	void SetAttributeData(GLuint& buffer, const GLsizeiptr size, const void * data, GLenum usage,
		GLuint locationIndex, const GLuint components);
};
