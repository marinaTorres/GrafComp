#include "Mesh.h"

Mesh::Mesh(){
	_vertexArrayObject = 0;
	_positionsVertexBufferObject = 0;
	_colorsVertexBufferObject = 0;
	_vertexCount = 0;
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &_positionsVertexBufferObject);
	glDeleteBuffers(1, &_colorsVertexBufferObject);
	glDeleteVertexArrays(1, &_vertexArrayObject);
}

void Mesh::CreateMesh(GLuint vertexCount){
	_vertexCount = vertexCount;
	// Queremos generar 1 manager
	glGenVertexArrays(1, &_vertexArrayObject);
}

void Mesh::Draw(GLenum primitive){
	// Utilizar el vao
	// A partir de este momento, todos los VBOs creados y configurados se van a asociar a este manager
	glBindVertexArray(_vertexArrayObject);
	// Función de dibujado SIN índices a partir de qué vértice y cuántos más se dibujarán
	//glDrawArrays(GL_TRIANGLE_FAN, 0, clamp( vertsPerFrame, 0.0f, 362.0f));
	//glDrawArrays(GL_TRIANGLE_FAN, 0, 362.0f);
	glDrawArrays(primitive, 0, 12);
	// Terminamos de utilizar el manager vao
	glBindVertexArray(0);

}

void Mesh::SetPositionAttribute(vector<vec2> positions, GLenum usage, GLuint locationIndex){
	if (positions.size() == 0 || positions.size() != _vertexCount) {
		return;
	}
	else {
		SetAttributeData(_positionsVertexBufferObject, sizeof(glm::vec2) * positions.size(), positions.data(), usage, locationIndex, 2);
	}
}

void Mesh::SetPositionAttribute(vector<vec3> positions, GLenum usage, GLuint locationIndex) {
	if (positions.size() == 0 || positions.size() != _vertexCount) {
		return;
	}
	else {
		SetAttributeData(_positionsVertexBufferObject, sizeof(glm::vec3) * positions.size(), positions.data(), usage, locationIndex, 2);
	}
}

void Mesh::SetColorAttribute(vector<vec3> colors, GLenum usage, GLuint locationIndex){
	if (colors.size() == 0 || colors.size() != _vertexCount) {
		return;
	}
	else {
		SetAttributeData(_colorsVertexBufferObject, sizeof(glm::vec3) * colors.size(), colors.data(), usage, locationIndex, 3);
	}	
}

void Mesh::SetColorAttribute(vector<vec4> colors, GLenum usage, GLuint locationIndex) {
	if (colors.size() == 0 || colors.size() != _vertexCount) {
		return;
	}
	else {
		SetAttributeData(_colorsVertexBufferObject, sizeof(glm::vec4) * colors.size(), colors.data(), usage, locationIndex, 3);
	}
}

void Mesh::SetAttributeData(GLuint & buffer, const GLsizeiptr size, const void * data, GLenum usage, GLuint locationIndex, const GLuint components){
	if (buffer != 0){
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(_vertexArrayObject);
	glGenBuffers(1, &buffer);
	// Activamos el buffer de posiciones para poder utilizarlo, este buffer ES UN ATRIBUTO (GL ARRAY BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	// Creamos la memoria y la inicializamos con los datos del atributo de posiciones
	glBufferData(GL_ARRAY_BUFFER,size,data,usage);
	// Activamos el atributo en la tarjeta de video
	glEnableVertexAttribArray(locationIndex);
	// Configuramos los datos del atributo en la tarjeta de video
	glVertexAttribPointer(locationIndex, components, GL_FLOAT, GL_FALSE, 0, nullptr);
	// Ya no vamos a utilizar este Vertex Buffer Object en este momento
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
