#include "ShaderProgram.h"
#include <string>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

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
	// Asociamos un buffer con �ndice 0 (posiciones) a la variable VertexPosition
	glBindAttribLocation(_programHandle, locationIndex,name.c_str());
}

void ShaderProgram::SetUniformf(string name, float value){
	//para configurar un uniform, tenemos que 
	//decirle a openGL que vamos a utilizar 
	//shader program(manage)
	
	GLint  uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform1f(uniformLocation, value);
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

void ShaderProgram::DeleteAndDetachShaders(){
	_attachedShaders.clear();
}

void ShaderProgram::DeleteProgram(){
	DeleteAndDetachShaders();
	glUseProgram(0);
}
