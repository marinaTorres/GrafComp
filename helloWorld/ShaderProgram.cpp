#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(){
	_programHandle = 0;
}

ShaderProgram::~ShaderProgram(){
	DeleteProgram();
}

void ShaderProgram::CreateProgram(){
	// Regresa el identificador de este manager
	// Creamos el identificador para el manager de los shaders
	_programHandle = glCreateProgram();

}

void ShaderProgram::AttachShader(string path, GLenum type){
	// Create and add the shaders to a list
	unique_ptr<Shader> shader(new Shader);
	shader->CreateShader(path, type);
	_attachedShaders.push_back(move(shader));
}

void ShaderProgram::LinkProgram(){
	for (int i = 0; i<_attachedShaders.size(); i++){
		glAttachShader(_programHandle, _attachedShaders.at(i).get()->getHandle());
	}
	glLinkProgram(_programHandle);
	DeleteAndDetachShaders();
}

void ShaderProgram::Activate(){
	// Activamos el vertexShader y el fragmentShader utilizando el manager
	glUseProgram(_programHandle);
}

void ShaderProgram::Desactivate(){
	// Desactivamos el manager shaderProgram
	glUseProgram(0);
}

void ShaderProgram::SetAttribute(GLuint locationIndex, string name){
	// Asociamos un buffer con índice 0 (posiciones) a la variable VertexPosition
	glBindAttribLocation(_programHandle, locationIndex,name.c_str());
}

void ShaderProgram::SetUniformf(string name, float value){
	//para configurar un uniform, tenemos que 
	//decirle a openGL que vamos a utilizar 
	//shader program(manage)
	
	GLint  uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform1f(uniformLocation, value);
}

void ShaderProgram::SetUniformI(string name, int value){
	GLint  uniformLocation = glGetUniformLocation(_programHandle, (const GLchar*)name.c_str());
	glUniform1i(uniformLocation, value);

}

void ShaderProgram::SetUniformf(string name, float x, float y){
	GLint  uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform2f(uniformLocation, x, y);
}

void ShaderProgram::SetUniformf(string name, float x, float y, float z){
	GLint  uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform3f(uniformLocation, x, y, z);
}

void ShaderProgram::SetUniformf(string name, float x, float y, float z, float w){
	GLint  uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform4f(uniformLocation, x, y, z, w);
}

void ShaderProgram::SetUniformMatrix(string name, mat4 matrix){
	GLuint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, value_ptr(matrix));
}

void ShaderProgram::SetUniformMatrix3(string name, glm::mat3 matrix){
	GLint uniformLocation = glGetUniformLocation(_programHandle, (const GLchar*)name.c_str());
	glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::DeleteAndDetachShaders(){
	for (int i = 0; i < _attachedShaders.size(); i++) {
		glDetachShader(_programHandle, _attachedShaders[i].get()->getHandle());
	}
		_attachedShaders.clear();
}

void ShaderProgram::DeleteProgram(){
	DeleteAndDetachShaders();
	glDeleteProgram(_programHandle);
}
