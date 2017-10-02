#include "Shader.h"
#include "inputFile.h"

Shader::Shader(){
	_shaderHandle = 0;
}

Shader::~Shader(){
	glDeleteShader(_shaderHandle);
}

void Shader::CreateShader(string path, GLenum type){
	// Creamos un objeto para leer archivos
	inputFile myfile;

	// VERTEX SHADER
	// Leemos el archivo Default.vert donde está el código del vertex shader.
	myfile.read(path);
	// Obtenemos el código fuente y lo guardamos en un string
	string ShaderSource = myfile.getContents();
	// Creamos un shader de tipo vertex guardamos su identificador en una variable
	GLuint _shaderHandle = glCreateShader(type);

	// Obtener los datos en el formato correcto: Vil Cast
	const GLchar *ShaderSource_c = (const GLchar*)ShaderSource.c_str();
	// Le estamos dando el código fuente a OpenGL para que se los asigne al shader
	glShaderSource(_shaderHandle, 1, &ShaderSource_c, nullptr);
	// Compilamos el shader en busca de errores.
	// Vamos a asumir que no hay ningún error.
	glCompileShader(_shaderHandle);
}

GLuint Shader::getHandle(){
	return _shaderHandle;
}
