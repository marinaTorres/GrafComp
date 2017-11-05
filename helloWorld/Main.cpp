/*********************************************************
Materia: Gráficas Computacionales
Fecha: 26 de Octubre del 2017
Autor: A01374526 José Karlo Hurtado Corona
Autor: A01375051 Marina Fernanda Torres Gomez
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
#include "Texture2D.h"
#include <IL/il.h>

using namespace std;
using namespace glm;


//Animación
float vertsPerFrame = 0.0f;
float delta = 0.0f;
float delta2 = 0.0f;
bool d2 = false;
float MAN = (delta2 / 360) / 2;

//Posicion de la camara
vec3 camaraPos = vec3(0.0f, 0.0f, 50.0f);

Mesh mesh;
ShaderProgram program;
Transform _transform;
Transform _transform2;
Camera _camera;

//Texturas
Texture2D _myTexture;
Texture2D _floor;
Texture2D _logo;

void Initialize() {
	// Creando toda la memoria una sola vez al inicio de vida de mi programa
	// Vector de C++ es una lista de elementos, vector de glm es una matriz con muchos componentes
	// Lista de vec2
	// Claramente estamos trabajando en el CPU y RAM

	// Tantos colores por número de vertices tengas, si un vértice tiene un atributo, todos deben tenerlo
	// Arreglo de colors en el CPU

	vector<vec3> positions;
	//vector<vec3> colors;
	vector<vec3> normals;
	vector<vec2> textures;
	//Cubo
	/*
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
	*/


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

	//++++++++++++++++++++++Normals++++++++++++++++++++++\\
	//Delantera
	normals.push_back(vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(vec3(0.0f, 0.0f, 1.0f));

	//Atras
	normals.push_back(vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(vec3(0.0f, 0.0f, -1.0f));

	//Derecha
	normals.push_back(vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(vec3(1.0f, 0.0f, 0.0f));

	//izquierda
	normals.push_back(vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(vec3(-1.0f, 0.0f, 0.0f));

	//Arriba
	normals.push_back(vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(vec3(0.0f, 1.0f, 0.0f));

	//Abajo
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));

	//++++++++++++++++++++++Texturas++++++++++++++++++++++\\
	//frontal
	textures.push_back(vec2(1.0f, 0.0f));
	textures.push_back(vec2(1.0f, 1.0f));
	textures.push_back(vec2(0.0f, 0.0f));
	textures.push_back(vec2(0.0f, 1.0f));

	//Atras
	textures.push_back(vec2(1.0f, 0.0f));
	textures.push_back(vec2(1.0f, 1.0f));
	textures.push_back(vec2(0.0f, 0.0f));
	textures.push_back(vec2(0.0f, 1.0f));

	//izquierda
	textures.push_back(vec2(1.0f, 0.0f));
	textures.push_back(vec2(1.0f, 1.0f));
	textures.push_back(vec2(0.0f, 0.0f));
	textures.push_back(vec2(0.0f, 1.0f));

	//Derecha
	textures.push_back(vec2(1.0f, 0.0f));
	textures.push_back(vec2(1.0f, 1.0f));
	textures.push_back(vec2(0.0f, 0.0f));
	textures.push_back(vec2(0.0f, 1.0f));

	//Superior
	textures.push_back(vec2(1.0f, 0.0f));
	textures.push_back(vec2(1.0f, 1.0f));
	textures.push_back(vec2(0.0f, 0.0f));
	textures.push_back(vec2(0.0f, 1.0f));

	//Inferior
	textures.push_back(vec2(1.0f, 0.0f));
	textures.push_back(vec2(1.0f, 1.0f));
	textures.push_back(vec2(0.0f, 0.0f));
	textures.push_back(vec2(0.0f, 1.0f));

	//++++++++++++++++++++++Indices y más...++++++++++++++++++++++\\
													   	
	vector<unsigned int> indices = 
	{ 0, 1, 2, 2, 1, 3,
	  4, 5, 6, 6, 5, 7,
	  8, 9, 10, 10, 9, 11,
	  12, 13, 14, 14, 13, 15,
	  16, 17, 18, 18, 17, 19,
	  20, 21, 22, 22, 21, 23 };

	//Luz
	vec3 LightColour = vec3(1.0f, 1.0f, 1.0f);
	vec3 lSource = vec3(18.0f, 0.0f, 20.0f);

	//texturas
	_myTexture.LoadTexture("colors.jpg");
	_floor.LoadTexture("cubo_morado.jpg");
	_logo.LoadTexture("Paramore_Logo.png");

	mesh.CreateMesh(positions.size());
	mesh.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	//mesh.SetColorAttribute(colors, GL_STATIC_DRAW, 1);
	mesh.SetNormalAttribute(normals, GL_STATIC_DRAW, 1);
	mesh.SetTexCoordAttribute(textures, GL_STATIC_DRAW, 2);
	mesh.SetIndices(indices, GL_STATIC_DRAW);



	program.CreateProgram();
	program.AttachShader("Default.vert", GL_VERTEX_SHADER);
	program.AttachShader("Default.frag", GL_FRAGMENT_SHADER);
	program.SetAttribute(0, "VertexPosition");
	//program.SetAttribute(1, "VertexColor");
	program.SetAttribute(1, "VertexNormal");
	program.SetAttribute(2, "VertexTexCoord");
	program.LinkProgram();


	program.Activate();
	program.SetUniformf("Resolution", 400.0f, 400.0f);
	program.SetUniformf("LightColor", LightColour.x, LightColour.y, LightColour.z);
	program.SetUniformf("LightPosition", lSource.x, lSource.y, lSource.z);
	program.SetUniformf("CameraPosition", camaraPos.x, camaraPos.y, camaraPos.z);
	program.SetUniformI("DiffuseTexture", 0);
	program.SetUniformI("DiffuseTexture2", 1);

	program.Desactivate();

	_camera.SetPosition(camaraPos.x, camaraPos.y, camaraPos.z);
	_transform.SetScale(2, 2, 2);
	_transform.SetRotation(0.0f, 25.0f, 0.0f);
	_transform2.SetScale(30.0f, 0.5f, 30.0f);
	_transform2.SetPosition(0.0f, -15.0f, 0.0f);
	_transform2.SetRotation(0.0f, 0.0f, 0.0f);

	/*
	// Cambio de escala de la geometría1 a 3 veces su tamaño original en los 3 ejes
	_transform.SetScale(3, 3, 3);
	// Inicialmente la geometría2 empieza con una escala de 0.5
	_transform2.SetScale(0.5f, 0.5f, 0.5f);
	// La posición de la geometría2 siempre está en (0,0,0)
	_transform2.SetPosition(0, 0, 0);
	// Colocando la cámara en (0, 0, 25) para visualizar correctamente las dos geometrías
	_camera.SetPosition(0, 0, 25);

	//PENTÁGONO
	float arr[6] = { 18.f, 306.f, 234.f, 162.f, 90.f, 18.f };
	for (int i = 0; i < 6; i++) {
	positions.push_back(vec2(cos(radians(arr[i])), sin(radians(arr[i]))));
	positions.push_back(vec2(3.0*cos(radians(arr[i])), 3.0*sin(radians(arr[i]))));
	}
	//Triángulo
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
	//para configurar un uniform, tenemos que
	//decirle a openGL que vamos a utilizar
	//shader program(manage)
	glUseProgram(shaderProgram);
	GLint  uniformLocation = glGetUniformLocation(shaderProgram, "Resolution");
	glUniform2f(uniformLocation,400.0f,400.0f);
	glUseProgram(0);
	positions.push_back(vec2(0.0f, 0.0f));
	int i = 0;
	float x, y;
	float radian;
	for (i; i <= 360; i++) {
	radian = i*0.01745329252f;
	x = 1 * cos(radian);
	y = 1 * sin(radian);
	positions.push_back(vec2(x,y));
	}
	colors.push_back(glm::vec3(1.0, 1.0, 1.0));
	double z;
	i = 0;
	for (i; i <= 360; i++) {
	radian = i*0.01745329252f;
	x = 1 * cos(radian);
	y = 1 * sin(radian);
	z = sin(radian)*cos(radian);
	colors.push_back(glm::vec3(x, y, z));
	}
	void mainImage( out vec4 fragColor, in vec2 fragCoord )
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

	if (delta == 360) {
		delta = 0;
	}
	_transform.Rotate(-0.01f, -0.01f, 0.01f, false);

	program.Activate();

	//Geometria 1
	glActiveTexture(GL_TEXTURE0);
	_myTexture.Bind();
	glActiveTexture(GL_TEXTURE1);
	_logo.Bind();
	mat4 matModelo = _transform.GetModelMatrix();
	mat3 normalMatrix = transpose(inverse(mat3(_transform.GetModelMatrix())));
	program.SetUniformMatrix("modelMatrix", matModelo);
	program.SetUniformMatrix3("normalMatrix", normalMatrix);
	program.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix());
	mesh.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_myTexture.Unbind();
	glActiveTexture(GL_TEXTURE1);
	_logo.Unbind();

	////Geometria 2
	glActiveTexture(GL_TEXTURE0);
	_floor.Bind();
	mat4 matModelo2 = _transform2.GetModelMatrix();
	mat3 normalMatrix2 = transpose(inverse(mat3(_transform2.GetModelMatrix())));
	program.SetUniformMatrix("modelMatrix", matModelo2);
	program.SetUniformMatrix3("normalMatrix", normalMatrix2);
	program.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform2.GetModelMatrix());
	mesh.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_floor.Unbind();
	
	program.Desactivate();

	glutSwapBuffers();

	delta += 0.01f;
	if (delta2 >= 360) {
		d2 = true;
	}
	if (delta2 <= -180) {
		d2 = false;
	}

	if (d2 == true) {
		delta2 -= 0.1f;
	}
	else {
		delta2 += 0.1f;
	}
	MAN = (delta2 / 360) / 2;

	/*

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

	vertsPerFrame += delta;
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
	//inicializa freglut
	//este crea ventana
	//en donde se dibuja
	glutInit(&argc, argv);
	//INICIA EL CONTEXTO DE OPENGL; ESTO SON SUS CAPACIDADES GRAFICAS
	//En este caso se usa pipeline Programable
	glutInitContextProfile(GLUT_CORE_PROFILE);
	//SOLICITANDO VERSION 4.4 DE GL 
	glutInitContextVersion(4, 2);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	//freeglut nos permite configurar eventos que ocurren en la ventana
	//nos interesa cuando alguien cierra la ventana, en ese caso se deja de renderear la escena.

	//configuramos el framebuffer, true color RGBA profundidad y un segundo buffer para rendereo
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	//la ventana 
	glutInitWindowSize(400, 400);

	//su titulo e inicialización
	glutCreateWindow("HELLO WORLD GL ");

	glutDisplayFunc(GameLoop);

	//asociamos una funicon para el cambio de resolucion de la ventana, se va amandar a llamar cuando alguien cambie el tamaño
	glutReshapeFunc(ReshapeWindow);
	glutIdleFunc(Idle);
	//inicializa glew y se encarga de obtener el api de opengl de nuestra video card
	glewInit();

	//Config OpenGL
	//este es el color por default en el buffer del color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	//borrado de caras traseras, todos los triangulos CCW
	//glEnable(GL_CULL_FACE);
	//No dibujar las caras de atras
	//glEnable(GL_BACK);

	//-----------------------------------------------------------------
	// Inicializar DevIL. Esto se debe hacer sólo una vez.
	ilInit();
	// Cambiar el punto de origen de las texturas. Por default, DevIL
	// pone un punto de origen en la esquina superior izquierda.
	// Esto es compatible con el sistema operativo, pero no con el
	// funcionamiento de OpenGL. 
	ilEnable(IL_ORIGIN_SET);
	// Configurar el punto de origen de las texturas en la esquina 
	// inferior izquierda
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	//-----------------------------------------------------------------

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//config inicial del programa.
	Initialize();

	//Inicia la aplicación, el main se pausa en esta linea hasta que se cierre la ventana
	glutMainLoop();

	return 0;
}