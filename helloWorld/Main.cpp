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


float pos = 0.0; // Índice para la trayectoria del círculo de la geometría1
float deltaCirculo = 0.01f;
float inc = 0.0; // Incremento en la escala de la geometría2
float deltaEscala = 0.00005f;
double colour = 0.0; // Color de fondo

Mesh mesh;
ShaderProgram program;
Transform _transform;
Transform _transform2;
Camera _camera;

void Initialise() {
	// Creando toda la memoria una sola vez al inicio de vida de mi programa
	// Vector de C++ es una lista de elementos, vector de glm es una matriz con muchos componentes
	// Lista de vec2
	// Claramente estamos trabajando en el CPU y RAM

	// Tantos colores por número de vertices tengas, si un vértice tiene un atributo, todos deben tenerlo
	// Arreglo de colors en el CPU

	//PENTÁGONO
	/*float arr[6] = { 18.f, 306.f, 234.f, 162.f, 90.f, 18.f };
	for (int i = 0; i < 6; i++) {
		positions.push_back(vec2(cos(radians(arr[i])), sin(radians(arr[i]))));
		positions.push_back(vec2(3.0*cos(radians(arr[i])), 3.0*sin(radians(arr[i]))));
	}


	 Cubo
	//++++++++++++++++++++++Colors++++++++++++++++++++++\\

	//Cara Frontal-MORADO
	colors.push_back(vec3(0.545f, 0.000f, 0.545f));
	colors.push_back(vec3(0.600f, 0.196f, 0.800f));
	colors.push_back(vec3(0.580f, 0.000f, 0.827f));
	colors.push_back(vec3(0.541f, 0.169f, 0.886f));

	//Cara Lateral Izquierda-VERDE
	colors.push_back(vec3(0.596f, 0.984f, 0.596f));
	colors.push_back(vec3(0.565f, 0.933f, 0.565f));
	colors.push_back(vec3(0.000f, 0.980f, 0.604f));
	colors.push_back(vec3(0.000f, 1.000f, 0.498f));


	//Cara posterior-ROSA
	colors.push_back(vec3(1.000f, 0.412f, 0.706f));
	colors.push_back(vec3(1.000f, 0.078f, 0.576f));
	colors.push_back(vec3(0.780f, 0.082f, 0.522f));
	colors.push_back(vec3(0.859f, 0.439f, 0.576f));


	//Cara lateral Derecha-NARANJA
	colors.push_back(vec3(1.000f, 0.627f, 0.478f));
	colors.push_back(vec3(1.000f, 0.498f, 0.314f));
	colors.push_back(vec3(1.000f, 0.388f, 0.278f));
	colors.push_back(vec3(1.000f, 0.271f, 0.000f));

	//cara Superior-AZUL
	colors.push_back(vec3(0.373f, 0.620f, 0.627f));
	colors.push_back(vec3(0.275f, 0.510f, 0.706f));
	colors.push_back(vec3(0.690f, 0.769f, 0.871f));
	colors.push_back(vec3(0.690f, 0.878f, 0.902f));

	//cara Inferior-GRIS
	colors.push_back(vec3(0.502f, 0.502f, 0.502f));
	colors.push_back(vec3(0.412f, 0.412f, 0.412f));
	colors.push_back(vec3(0.467f, 0.533f, 0.600f));
	colors.push_back(vec3(0.439f, 0.502f, 0.565f));
	


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
									0, 1, 2, 2, 1, 3,
									8, 9, 10, 10, 9, 11,
									4, 5, 6, 6, 5, 7,
									12, 13, 14, 14, 13, 15,
									16, 17, 18, 18, 17, 19,
									};*/
	
	vector<vec3> positions;
	vector<vec3> colors;
	//Posiciones
	//Punta
	positions.push_back(vec3(0.0f, 1.0f, 0.0f));//->0
	//base
	positions.push_back(vec3(1.0f, -1.0f, 1.0f));//->1
	positions.push_back(vec3(-1.0f, -1.0f, 1.0f));//->2
	positions.push_back(vec3(1.0f, -1.0f, -1.0f));//->3
	positions.push_back(vec3(-1.0f, -1.0f, -1.0f));//->4

	//Colores
	colors.push_back(vec3(0.545f, 0.000f, 0.545f));
	colors.push_back(vec3(0.596f, 0.984f, 0.596f));
	colors.push_back(vec3(1.000f, 0.412f, 0.706f));
	colors.push_back(vec3(0.373f, 0.620f, 0.627f));
	colors.push_back(vec3(0.502f, 0.502f, 0.502f));

	vector<unsigned int> indices = {0,2,1,1,0,3,3,0,4,4,0,2,1,3,2,2,3,4};
	mesh.CreateMesh(positions.size());
	mesh.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	mesh.SetColorAttribute(colors, GL_STATIC_DRAW, 1);
	mesh.SetIndices(indices, GL_STATIC_DRAW);
	
	

	program.CreateProgram();
	program.AttachShader("Default.vert", GL_VERTEX_SHADER);
	program.AttachShader("Default.frag", GL_FRAGMENT_SHADER);
	program.SetAttribute(0, "VertexPosition");
	program.SetAttribute(1, "VertexColor");
	program.LinkProgram();
	
	//_transform.SetRotation(0.0f, 0.0f, 45.0f);
	//_camera.SetOrthographic(6.0f, 1.0f);
	
	// Cambio de escala de la geometría1 a 3 veces su tamaño original en los 3 ejes
	_transform.SetScale(3, 3, 3);

	// Inicialmente la geometría2 empieza con una escala de 0.5
	_transform2.SetScale(0.5f, 0.5f, 0.5f);
	// La posición de la geometría2 siempre está en (0,0,0)
	_transform2.SetPosition(0, 0, 0);

	// Colocando la cámara en (0, 0, 25) para visualizar correctamente las dos geometrías
	_camera.SetPosition(0, 0, 25);



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
	//_transform.Rotate(0.01f, 0.01f, 0.01f, true);//Rotación Global
	//_transform.Rotate(0.01f, 0.01f, 0.01f, false);//Rotación Local

	// Geometría1 rota en sus tres ejes coordenados
	_transform.Rotate(0.03f, 0.015f, 0.03f, false);
	// Geometría1 sigue una trayectoria circular en el plano XY
	_transform.SetPosition(5 * cos(radians(pos)), 5 * sin(radians(pos)), 0);
	pos += deltaCirculo;

	// Geometría2 rota en sus tres ejes coordenados, pero en sentido contrario
	_transform2.Rotate(-0.03f, -0.015f, -0.03f, false);

	// Incrementar la escala de la geometría2 en el rango de 0.25 -> 1.0
	_transform2.SetScale(0.5f + inc, 0.5f + inc, 0.5f + inc);
	if (_transform2.GetScale().x <= 0.25f || _transform2.GetScale().x >= 1.0f) {
		deltaEscala *= -1.0f;
	}
	inc += deltaEscala;

	program.Activate();
	
	program.SetUniformMatrix("mvplMatrix",_camera.GetViewProjection()* _transform.GetModelMatrix());
	mesh.Draw(GL_TRIANGLES);

	program.SetUniformMatrix("mvplMatrix", _camera.GetViewProjection()* _transform2.GetModelMatrix());
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
	//glEnable(GL_CULL_FACE);
	//No dibujar las caras de atras
	//glEnable(GL_BACK);
	cout << glGetString(GL_VERSION) << endl;
	// Configurar OpenGl. Este es el color por dedault del buffer de color en el framebuffer.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	cout << glGetString(GL_VERSION) << endl;

	// Configuración inicial de nuestro programa
	Initialise();

	// Iniciar la aplicación. El Main se pausará en esta línea hasta que se cierre la ventana.
	glutMainLoop();

	return 0;
}