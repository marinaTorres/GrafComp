/*********************************************************
Materia: Gráficas Computacionales
Fecha: 18 de agosto del 2017
Autor: A01375051 Marina Fernanda Torres Gómez
*********************************************************/

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>

#include "inputFile.h"
#include "Mesh.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Camera.h"
using namespace std;
using namespace glm;


//float vertsPerFrame = 0.0f;
//float delta = 0.08;

Mesh mesh;
ShaderProgram program;
Transform _transform;
Camera _camera;

void Initialise() {
	// Creando toda la memoria una sola vez al inicio de vida de mi programa
	// Vector de C++ es una lista de elementos, vector de glm es una matriz con muchos componentes
	// Lista de vec2
	// Claramente estamos trabajando en el CPU y RAM

	
	vector<vec3> positions;
	vector<vec3> colors;
	// Tantos colores por número de vertices tengas, si un vértice tiene un atributo, todos deben tenerlo
	// Arreglo de colors en el CPU

	//PENTÁGONO
	/*float arr[6] = { 18.f, 306.f, 234.f, 162.f, 90.f, 18.f };
	for (int i = 0; i < 6; i++) {
		positions.push_back(vec2(cos(radians(arr[i])), sin(radians(arr[i]))));
		positions.push_back(vec2(3.0*cos(radians(arr[i])), 3.0*sin(radians(arr[i]))));
	}*/


	//++++++++++++++++++++++Colors++++++++++++++++++++++\\

	//Cara Frontal-Purple
	colors.push_back(vec3(0.580f, 0.0f, 0.827f));
	colors.push_back(vec3(0.580f, 0.0f, 0.827f));
	colors.push_back(vec3(0.580f, 0.0f, 0.827f));
	colors.push_back(vec3(0.580f, 0.0f, 0.827f));
	
	//Cara Posterior-Pink
	colors.push_back(vec3(0.933f, 0.510f, 0.933f));
	colors.push_back(vec3(0.933f, 0.510f, 0.933f));
	colors.push_back(vec3(0.933f, 0.510f, 0.933f));
	colors.push_back(vec3(0.933f, 0.510f, 0.933f));

	
	//Cara Lateral Derecha-Blue
	colors.push_back(vec3(0.125f, 0.698f, 0.667f));
	colors.push_back(vec3(0.125f, 0.698f, 0.667f));
	colors.push_back(vec3(0.125f, 0.698f, 0.667f));
	colors.push_back(vec3(0.125f, 0.698f, 0.667f));
	

	//Cara lateral Izquierda-Yellow
	colors.push_back(vec3(1.000f, 1.000f, 0.000f));
	colors.push_back(vec3(1.000f, 1.000f, 0.000f));
	colors.push_back(vec3(1.000f, 1.000f, 0.000f));
	colors.push_back(vec3(1.000f, 1.000f, 0.000f));
	
	//cara Superior-White
	colors.push_back(vec3(1.0f, 1.0f, 1.0f));
	colors.push_back(vec3(1.0f, 1.0f, 1.0f));
	colors.push_back(vec3(1.0f, 1.0f, 1.0f));
	colors.push_back(vec3(1.0f, 1.0f, 1.0f));
	
	//cara Inferior-Lima
	colors.push_back(vec3(0.486f, 0.988f, 0.000f));
	colors.push_back(vec3(0.486f, 0.988f, 0.000f));
	colors.push_back(vec3(0.486f, 0.988f, 0.000f));
	colors.push_back(vec3(0.486f, 0.988f, 0.000f));
	

	//++++++++++++++++++++++Positions++++++++++++++++++++++\\

	//Cara Frontal
	positions.push_back(vec3(3.0f, -3.0f, 3.0f));//->0
	positions.push_back(vec3(3.0f, 3.0f, 3.0f));//->1
	positions.push_back(vec3(-3.0f, -3.0f, 3.0f));//->2
	positions.push_back(vec3(-3.0f, 3.0f, 3.0f));//->3

	//Cara Posterior
	positions.push_back(vec3(3.0f, -3.0f, -3.0f));//->4
	positions.push_back(vec3(3.0f, 3.0f, -3.0f));//->5
	positions.push_back(vec3(-3.0f, -3.0f, -3.0f));//->6
	positions.push_back(vec3(-3.0f, 3.0f, -3.0f));//->7

	//Cara Lateral Derecha
	positions.push_back(vec3(3.0f, -3.0f, -3.0f));//->8
	positions.push_back(vec3(3.0f, 3.0f, -3.0f));//->9
	positions.push_back(vec3(3.0f, -3.0f, 3.0f));//->10
	positions.push_back(vec3(3.0f, 3.0f, 3.0f));//->11

	//Cara Lateral Izquierda
	positions.push_back(vec3(-3.0f, -3.0f, -3.0f));//->12
	positions.push_back(vec3(-3.0f, 3.0f, -3.0f));//->13
	positions.push_back(vec3(-3.0f, -3.0f, 3.0f));//->14
	positions.push_back(vec3(-3.0f, 3.0f, 3.0f));//->15


	//Cara Superior
	positions.push_back(vec3(3.0f, 3.0f, 3.0f));//->16
	positions.push_back(vec3(3.0f, 3.0f, -3.0f));//->17
	positions.push_back(vec3(-3.0f, 3.0f, 3.0f));//->18
	positions.push_back(vec3(-3.0f, 3.0f, -3.0f));//->19

	//Cara Inferior
	positions.push_back(vec3(3.0f, -3.0f, 3.0f));//->20
	positions.push_back(vec3(3.0f, -3.0f, -3.0f));//->21
	positions.push_back(vec3(-3.0f, -3.0f, 3.0f));//->22
	positions.push_back(vec3(-3.0f, -3.0f, -3.0f));//->23


	
	//++++++++++++++++++++++Indices y más...++++++++++++++++++++++\\

	vector<unsigned int> indices = {20,21,22,22,21,23,
									0,1,2,2,1,3,
									8,9,10,10,9,11,
									4,5,6,6,5,7,
									12,13,14,14,13,15,
									16,17,18,18,17,19,
									};

	

	mesh.CreateMesh(24);
	mesh.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	mesh.SetColorAttribute(colors, GL_STATIC_DRAW, 1);
	mesh.SetIndices(indices, GL_STATIC_DRAW);
	
	

	program.CreateProgram();
	program.AttachShader("Default.vert", GL_VERTEX_SHADER);
	program.AttachShader("Default.frag", GL_FRAGMENT_SHADER);
	program.SetAttribute(0, "VertexPosition");
	program.SetAttribute(1, "VertexColor");
	program.LinkProgram();
	
	_transform.SetRotation(0.0f, 0.0f, 45.0f);
	_camera.SetOrthographic(6.0f, 1.0f);

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
	vec2 q=p-vec2(3.0f,3.0f);

	vec3 color=vec3(3.0f,0.0f,3.0f);

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

	//_camera.MoveForward(0.0001f);
	_transform.Rotate(0.01f, 0.01f, 0.01f, true);//Rotación Global
	//_transform.Rotate(0.0f, 0.1f, 0.0f, false);//Rotación Local
	
	program.Activate();
	program.SetUniformMatrix("mvplMatrix",_camera.GetViewProjection()* _transform.GetModelMatrix());
	mesh.Draw(GL_TRIANGLES);
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
	// Freeglut se encargfa de crear una ventana en donde podemos dibujar Gráficas Computacionales
	glutInit(&argc, argv);
	glutInitContextVersion(4, 2);


	// Iniciar el contexto de OpenGL, se refiere a las capacidades de la aplicación gráfica
	// En este caso se trabaja con el pipeline progamable
	glutInitContextProfile(GLUT_CORE_PROFILE);

	// Freeglut nos permite configurar eventos que ocurren en la ventana
	// Un evento que interesa es cuando alguien cierra la ventana
	// En este caso, se deja de renderear la escena y se termina el programa
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// También configuramos frambuffer, en este caso solicitamos un buffer
	// true color RGBA, un buffer de produndidad y un segundo buffer para renderear
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); // Dos framebuffers

	// Iniciar las dimensiones de la ventana (en pixeles)
	glutInitWindowSize(400, 400);

	// Creeamos la ventana y le damos un título.
	glutCreateWindow("Hello World!");

	glutDisplayFunc(GameLoop);
		//asociamos una función ara el cambio de resolucion de la ventana.
		//freeglut la va a mandar a llamar 
		//cuando alguien cambie el tamaño de la ventana
	glutReshapeFunc(ReshapeWindow);

	//asociamos la función cuando openGL entra en estado de reposos
	glutIdleFunc(Idle);
	// Inicializamos GLEW. Esta librería se encarga de obtener el API de OpenGL de nuestra tarjeta de video
	glewInit();
	
	//Config OpenGL
	//este es el color por default en el buffer del color
	glClearColor(1.0f, 1.0f, 3.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	//borrado de caras traseras, todos los triangulos CCW
	glEnable(GL_CULL_FACE);
	//No dibujar las caras de atras
	glEnable(GL_BACK);
	std::cout << glGetString(GL_VERSION) << std::endl;
	// Configurar OpenGl. Este es el color por dedault del buffer de color en el framebuffer.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	cout << glGetString(GL_VERSION) << endl;

	// Configuración inicial de nuestro programa
	Initialise();

	// Iniciar la aplicación. El Main se pausará en esta línea hasta que se cierre la ventana.
	glutMainLoop();

	return 0;
}