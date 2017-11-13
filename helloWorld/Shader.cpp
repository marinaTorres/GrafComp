#include "Shader.h"
#include "inputFile.h"
#include <iostream>
#include <vector>

Shader::Shader(){
	_shaderHandle = 0;
}

Shader::~Shader(){
	glDeleteShader(_shaderHandle);
}

void Shader::CreateShader(string path, GLenum type){
	
	if (_shaderHandle != 0) {
		glDeleteShader(_shaderHandle);
	}
	
	// Creamos un objeto para leer archivos
	inputFile myfile;

	// VERTEX SHADER
	// Leemos el archivo Default.vert donde está el código del vertex shader.
	myfile.read(path);
	// Obtenemos el código fuente y lo guardamos en un string
	string ShaderSource = myfile.getContents();
	// Creamos un shader de tipo vertex guardamos su identificador en una variable
	_shaderHandle = glCreateShader(type);

	// Obtener los datos en el formato correcto: Vil Cast
	const GLchar *ShaderSource_c = (const GLchar*)ShaderSource.c_str();
	// Le estamos dando el código fuente a OpenGL para que se los asigne al shader
	glShaderSource(_shaderHandle, 1, &ShaderSource_c, nullptr);
	// Compilamos el shader en busca de errores.
	// Vamos a asumir que no hay ningún error.
	glCompileShader(_shaderHandle);

	// Get compile status
	GLint shaderCompileSuccess = 0;
	glGetShaderiv(_shaderHandle, GL_COMPILE_STATUS, &shaderCompileSuccess);
	if (shaderCompileSuccess == GL_FALSE)
	{
		// Get compile log length
		GLint logLength = 0;
		glGetShaderiv(_shaderHandle, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{

			// Allocate memory for compile log
			std::vector<GLchar> compileLog(logLength);

			// Get compile log
			glGetShaderInfoLog(_shaderHandle, logLength, &logLength, &compileLog[0]);

			// Print compile log
			for (int i = 0; i<logLength; i++)
				std::cout << compileLog[i];
			std::cout << std::endl;
		}
		std::cout << "Shader " << path << " did not compiled." << std::endl;

		//We don't need the shader anymore.
		glDeleteShader(_shaderHandle);

		return;
	}

	std::cout << "Shader " << path << " compiled successfully" << std::endl;
}

GLuint Shader::getHandle(){
	return _shaderHandle;
}
