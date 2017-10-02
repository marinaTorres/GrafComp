/*********************************************************
Materia: Gr�ficas Computacionales
Fecha: 18 de agosto del 2017
Autor: A01375051 Marina Fernanda Torres G�mez
*********************************************************/

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "inputFile.h"
#include "Mesh.h"
#include "Shader.h"
#include "ShaderProgram.h"

using namespace std;
using namespace glm;
/*++createMesh inicio++*/
// Identificadoe del manager al que vamos a asociar todos los VOBs que tenga nuestra geometr�a
GLuint vao;
/*++createMesh fin++*/

// Identificador del manager de los shaders (shaderProgramme)
GLuint shaderProgram;
//float vertsPerFrame = 0.0f;
//float delta = 0.08;

Mesh mesh;
ShaderProgram program;

void Initialise() {
	// Creando toda la memoria una sola vez al inicio de vida de mi programa
	// Vector de C++ es una lista de elementos, vector de glm es una matriz con muchos componentes
	// Lista de vec2
	// Claramente estamos trabajando en el CPU y RAM

	
	vector<vec2> positions;
	positions.push_back(vec2(0.9f, 0.3f));
	positions.push_back(vec2(0.5f, 0.19f));
	positions.push_back(vec2(0.6f, -0.8f));
	positions.push_back(vec2(0.3f, -0.4f));
	positions.push_back(vec2(-0.6f, -0.8f));
	positions.push_back(vec2(-0.3f, -0.4f));
	positions.push_back(vec2(-0.88f, 0.3f));
	positions.push_back(vec2(-0.5f, 0.19f));
	positions.push_back(vec2(0.0f, 0.9f));
	positions.push_back(vec2(0.0f, 0.5f));
	positions.push_back(vec2(0.9f, 0.3f));
	positions.push_back(vec2(0.5f, 0.19f));

	// Tantos colores por n�mero de vertices tengas, si un v�rtice tiene un atributo, todos deben tenerlo
	// Arreglo de colors en el CPU
	vector<vec3> colors;
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(vec3(1.0f, 0.0f, 1.0f));
	colors.push_back(vec3(1.0f, 0.0f, 1.0f));
	colors.push_back(vec3(1.0f, 0.0f, 1.0f));

	
	
	mesh.CreateMesh(12);
	mesh.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	mesh.SetColorAttribute(colors, GL_STATIC_DRAW, 1);

	program.CreateProgram();
	program.SetAttribute(0, "VertexPosition");
	program.SetAttribute(1, "VertexColor");
	program.AttachShader("Default.vert", GL_VERTEX_SHADER);
	program.AttachShader("Default.frag", GL_FRAGMENT_SHADER);
	program.LinkProgram();
	
	

	//para configurar un uniform, tenemos que 
	//decirle a openGL que vamos a utilizar 
	//shader program(manage)
	/*glUseProgram(shaderProgram);
	GLint  uniformLocation = glGetUniformLocation(shaderProgram, "Resolution");
	glUniform2f(uniformLocation,400.0f,400.0f);
	glUseProgram(0);*/

	/*positions.push_back(vec2(0.0f, 0.0f));
	int i = 0;
	float x, y;
	float radian;
	for (i; i <= 360; i++) {
	radian = i*0.01745329252f;
	x = 1 * cos(radian);
	y = 1 * sin(radian);
	positions.push_back(vec2(x,y));
	}

	*/

	/*colors.push_back(glm::vec3(1.0, 1.0, 1.0));

	double z;
	i = 0;
	for (i; i <= 360; i++) {
	radian = i*0.01745329252f;
	x = 1 * cos(radian);
	y = 1 * sin(radian);
	z = sin(radian)*cos(radian);
	colors.push_back(glm::vec3(x, y, z));
	}*/
	/*void mainImage( out vec4 fragColor, in vec2 fragCoord )
	{
	vec2 p =fragCoord/iResolution.xy;
	vec2 q=p-vec2(0.5f,0.5f);

	vec3 color=vec3(0.5f,0.0f,0.5f);

	float r=0.2f+0.1f*cos(atan(q.y,q.x)*10.0f+20.0f*q.x+1.0f);

	color*=smoothstep(r,r+0.1f,length(q));

	r=0.015f;
	r+=0.002*cos(120.0f*q.y);
	r+=exp(-40.0f*p.y);
	color*=1.0f-(1.0f-smoothstep(r,r+0.002,abs(q.x- 0.25f*sin(5.0f*q.y))))*  (1.0f-smoothstep(0.0f,0.01f,q.y));
	fragColor=vec4(color,1.0f);
	}
	*/
}

void GameLoop() {//esto es la tarea

	//Limpiamos el buffer de color y el buffer de profundidad
	// Siempre hacerlo al inicio del frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	program.Activate();
	mesh.Draw(GL_TRIANGLE_STRIP);
	program.Desactivate();


	glutSwapBuffers();
	/*vertsPerFrame += delta;
	if (vertsPerFrame<0.0f || vertsPerFrame>= 370.0f) {
		delta *= -1.0f;
	}*/

	//Cuando terminamos de renderear, cambiamos los buffers
	
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

void Idle() {
	//cuando entra en estado de reposo se vueve a dibujar
	glutPostRedisplay();
}

void ReshapeWindow(int w, int h) {
	glViewport(0, 0, w, h);
	/*glUseProgram(shaderProgram);
	GLint  uniformLocation = glGetUniformLocation(shaderProgram, "Resolution");
	glUniform2f(uniformLocation, w, h);
	glUseProgram(0);*/

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
		//asociamos una funci�n ara el cambio de resolucion de la ventana.
		//freeglut la va a mandar a llamar 
		//cuando alguien cambie el tama�o de la ventana
	glutReshapeFunc(ReshapeWindow);

	//asociamos la funci�n cuando openGL entra en estado de reposos
	glutIdleFunc(Idle);
	// Inicializamos GLEW. Esta librer�a se encarga de obtener el API de OpenGL de nuestra tarjeta de video
	glewInit();
	
	//Config OpenGL
	//este es el color por default en el buffer del color
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	//borrado de caras traseras, todos los triangulos CCW
	glEnable(GL_CULL_FACE);
	//No dibujar las caras de atras
	glEnable(GL_BACK);
	std::cout << glGetString(GL_VERSION) << std::endl;
	// Configurar OpenGl. Este es el color por dedault del buffer de color en el framebuffer.
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);

	cout << glGetString(GL_VERSION) << endl;

	// Configuraci�n inicial de nuestro programa
	Initialise();

	// Iniciar la aplicaci�n. El Main se pausar� en esta l�nea hasta que se cierre la ventana.
	glutMainLoop();

	return 0;
}