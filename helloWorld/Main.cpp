/*********************************************************
Materia: Gr�ficas Computacionales
Fecha: 18 de agosto del 2017
Autor: A01375051 Marina Fernanda Torres G�mez
*********************************************************/

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include "inputFile.h"
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

// Identificadoe del manager al que vamos a asociar todos los VOBs que tenga nuestra geometr�a
GLuint vao;

// Identificador del manager de los shaders (shaderProgramme)
GLuint shaderProgram;

void Initialise() {
	// Creando toda la memoria una sola vez al inicio de vida de mi programa
	// Vector de C++ es una lista de elementos, vector de glm es una matriz con muchos componentes
	// Lista de vec2
	// Claramente estamos trabajando en el CPU y RAM
	vector<vec2> positions;
	positions.push_back(vec2(0.5f, -0.5f));
	positions.push_back(vec2(0.5f, 0.5f));
	positions.push_back(vec2(-0.5f, -0.5f));
	positions.push_back(vec2(-0.5f, 0.5f));

	vector<vec3> colors;
	// Tantos colores por n�mero de vertices tengas, si un v�rtice tiene un atributo, todos deben tenerlo
	// Arreglo de colors en el CPU
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(vec3(1.0f, 0.0f, 1.0f));

	// Queremos gengerar 1 manager
	glGenVertexArrays(1, &vao);
	// Utilizar el vao
	// A partir de este momento, todos los VBOs creados y configurados se van a asociar a este manager
	glBindVertexArray(vao);

	// TIpo de dato de OpenGL entero sin signo multiplataforma
	// Empezamos a crear bufers (identificador de VBO de posiciones)
	GLuint positionsVBO;
	// Creaci�n del VBO de posiciones lo guarda en positionsVBO y da un identificador para utilizarlo
	glGenBuffers(1, &positionsVBO);
	// Activamos el buffer de posiciones para poder utilizarlo, este buffer ES UN ATRIBUTO (GL ARRAY BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	// Creamos la memoria y la inicializamos con los datos del atributo de posiciones
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2)*positions.size(), positions.data(), GL_STATIC_DRAW);
	// Activamos el atributo en la tarjeta de video
	glEnableVertexAttribArray(0);
	// Configuramos los datos del atributo en la tarjeta de video
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	// Ya no vamos a utilizar este Vertex Buffer Object en este momento
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint colorsVBO;
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*colors.size(), colors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desactivamos el manager vao
	glBindVertexArray(0);

	// Creamos un objeto para leer archivos
	inputFile myfile;

	// VERTEX SHADER
	// Leemos el archivo Default.vert donde est� el c�digo del vertex shader.
	myfile.read("Default.vert");
	// Obtenemos el c�digo fuente y lo guardamos en un string
	string vertexSource = myfile.getContents();
	// Creamos un shader de tipo vertex guardamos su identificador en una variable
	GLuint vertexShaderHandle =
		glCreateShader(GL_VERTEX_SHADER);
	// Obtener los datos en el formato correcto: Vil Cast
	const GLchar *vertexSource_c =
		(const GLchar*)vertexSource.c_str();
	// Le estamos dando el c�digo fuente a OpenGL para que se los asigne al shader
	glShaderSource(vertexShaderHandle, 1, &vertexSource_c, nullptr);
	// Compilamos el shader en busca de errores.
	// Vamos a asumir que no hay ning�n error.
	glCompileShader(vertexShaderHandle);

	myfile.read("Default.frag");
	string fragmentSource = myfile.getContents();
	GLuint fragmentShaderHandle =
		glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar *fragmentSource_c =
		(const GLchar*)fragmentSource.c_str();
	// Continuar leyendo hasta que encuentre un nullptr
	glShaderSource(fragmentShaderHandle, 1, &fragmentSource_c, nullptr);
	glCompileShader(fragmentShaderHandle);

	// Regresa el identificador de este manager
	// Creamos el identificador para el manager de los shaders
	shaderProgram = glCreateProgram();
	// Adjuntamos el vertex shader del manager (van a trabajar juntos)
	glAttachShader(shaderProgram, vertexShaderHandle);
	// Adjuntamos el fragment shader al manager (van a trabajar juntos)
	glAttachShader(shaderProgram, fragmentShaderHandle);
	// Asociamos un buffer con �ndice 0 (posiciones) a la variable VertexPosition
	glBindAttribLocation(shaderProgram, 0, "VertexPosition");
	// Asociamos un buffer con �ndice 1 (colores) a la variable VertexColor
	glBindAttribLocation(shaderProgram, 1, "VertexColor");
	//Ejecutamos el proceso de linker (asegurarnos que el vertex y fragment son compatibles)
	glLinkProgram(shaderProgram);
}

void GameLoop() {

	//Limpiamos el buffer de color y el buffer de profundidad
	// Siempre hacerlo al inicio del frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Activamos el vertexShader y el fragmentShader utilizando el manager
	glUseProgram(shaderProgram);

	// Activamos el manager y en este momento se activan todos los VBOs asociados autom�ticamente
	glBindVertexArray(vao);
	// Funci�n de dibujado SIN �ndices a partir de qu� v�rtice y cu�ntos m�s se dibujar�n
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	// Terminamos de utilizar el manager vao
	glBindVertexArray(0);

	// Desactivamos el manager shaderProgram
	glUseProgram(0);

	//Cuando terminamos de renderear, cambiamos los buffers
	glutSwapBuffers();
	
	/*
	// WARNING!!!!!! ESTO ES OPENGL VIEJITO!!!!!!

	glBegin(GL_TRIANGLES);

	//-1 para borde izquierdo, 1 para borde derecho, 0 centro, 1 arriba, -1 abajo
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-1.0f, -1.0f); // SOlo dos coordenadas, x y y , dos puntos o z para 3D pero este no tiene profundidad

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2d(1.0f, -1.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2d(0.0f, 1.0f);

	glEnd();*/
}

int main(int argc, char* argv[]) {
	// Inicializar freeglut
	// Freeglut se encargfa de crear una ventana en donde podemos dibujar Gr�ficas Computacionales
	glutInit(&argc, argv);
	glutInitContextVersion(4, 2);


	// Iniciar el contexto de OpenGL, se refiere a las capacidades de la aplicaci�n gr�fica
	// En este caso se trabaja con el pipeline progamable
	glutInitContextProfile(GLUT_CORE_PROFILE);

	// Freeglut nos permite configurar eventos que ocurren en la ventana
	// Un evento que interesa es cuando alguien cierra la ventana
	// En este caso, se deja de renderear la escena y se termina el programa
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// Tambi�n configuramos frambuffer, en este caso solicitamos un buffer
	// true color RGBA, un buffer de produndidad y un segundo buffer para renderear
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); // Dos framebuffers

															   // Iniciar las dimensiones de la ventana (en pixeles)
	glutInitWindowSize(400, 400);

	// Creeamos la ventana y le damos un t�tulo.
	glutCreateWindow("T�tulo Genial GL");

	glutDisplayFunc(GameLoop);

	// Inicializamos GLEW. Esta librer�a se encarga de obtener el API de OpenGL de nuestra tarjeta de video
	glewInit();

	// Configurar OpenGl. Este es el color por dedault del buffer de color en el framebuffer.
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);

	cout << glGetString(GL_VERSION) << endl;

	// Configuraci�n inicial de nuestro programa
	Initialise();

	// Iniciar la aplicaci�n. El Main se pausar� en esta l�nea hasta que se cierre la ventana.
	glutMainLoop();

	return 0;
}