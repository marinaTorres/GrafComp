/*********************************************************
Materia: Gráficas Computacionales
Fecha: 10 de noviembre del 2017
Autor: A01374526 José Karlo Hurtado Corona
Autor: A01375051 Marina Fernanda Torres Gomez
*********************************************************/

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <vector> 
#include <glm/glm.hpp>
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"
#include "Texture2D.h"
#include <IL/il.h>
#include "Dephtbuffer.h"


using namespace std;
using namespace glm;

#pragma region Global Scope vars

//manager al que le vamos a asociar todos los VBOs
GLuint vao;

//MANAGER DE los shaders (shaderProgram)
GLuint shaderProgram;
int g = 4;
int ULTRA = g * 6;

/*animacion
float vertsPerFrame = 0.0f;
float delta = 0.0f;
float delta2 = 0.0f;
bool d2 = false;
float MAN = (delta2 / 360) / 2;*/


//declaro shader program y mesh
ShaderProgram program;
ShaderProgram program2;
ShaderProgram program2Tex;
Mesh _mesh;

//LO del transform
Transform _transform;
Transform _transform2;
Camera _camera;
Camera _lightCamera;

//lo de la textura
Texture2D _back;
Texture2D _floor;
Texture2D _logo;

//el depth buffer
Dephtbuffer _myDephtbuffer;


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
	normals.push_back(vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(vec3(0.0f, -1.0f, 0.0f));

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
	vec3 lSource = vec3(0.0f, 20.0f, 0.0f);

	//textura
	_back.LoadTexture("colors.jpg");
	_floor.LoadTexture("cubo_morado.jpg");
	_logo.LoadTexture("Paramore_Logo.png");

	
	_mesh.CreateMesh(positions.size());
	_mesh.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	//_mesh.SetColorAttribute(colors(), GL_STATIC_DRAW, 1);
	_mesh.SetNormalAttribute(normals, GL_STATIC_DRAW, 2);
	_mesh.SetTexCoordAttribute(textures, GL_STATIC_DRAW, 3);
	_mesh.SetIndices(indices, GL_STATIC_DRAW);

	
	program2.CreateProgram();
	program2.AttachShader("Depth.vert", GL_VERTEX_SHADER);
	program2.AttachShader("Depth.frag", GL_FRAGMENT_SHADER);
	program2.SetAttribute(0, "VertexPosition");
	program2.LinkProgram();

	
	program.CreateProgram();
	program.AttachShader("Shadow.vert", GL_VERTEX_SHADER);
	program.AttachShader("Shadow.frag", GL_FRAGMENT_SHADER);
	program.SetAttribute(0, "VertexPosition");
	program.SetAttribute(1, "VertexColor");
	program.SetAttribute(2, "VertexNormal");
	program.SetAttribute(3, "VertexTexCoord");
	program.LinkProgram();

	program.Activate();
	program.SetUniformf("Resolution", 400.0f, 400.0f);
	program.SetUniformf("LightColor", LightColour.x, LightColour.y, LightColour.z);
	program.SetUniformf("LightPosition", lSource.x, lSource.y, lSource.z);
	program.SetUniformf("CameraPosition", 0.0f, 20.0f, 50.0f);
	program.SetUniformI("DiffuseTexture", 0);
	program.SetUniformI("DiffuseTexture2", 1);
	program.SetUniformI("ShadowMap", 2);
	program.Desactivate();
	
	program2Tex.CreateProgram();
	program2Tex.AttachShader("Shadow2Texturas.vert", GL_VERTEX_SHADER);
	program2Tex.AttachShader("Shadow2Texturas.frag", GL_FRAGMENT_SHADER);
	program2Tex.SetAttribute(0, "VertexPosition");
	program2Tex.SetAttribute(1, "VertexColor");
	program2Tex.SetAttribute(2, "VertexNormal");
	program2Tex.SetAttribute(3, "VertexTexCoord");

	program2Tex.LinkProgram();

	program2Tex.Activate();
	program2Tex.SetUniformf("Resolution", 400.0f, 400.0f);
	program2Tex.SetUniformf("LightColor", LightColour.x, LightColour.y, LightColour.z);
	program2Tex.SetUniformf("LightPosition", lSource.x, lSource.y, lSource.z);
	program2Tex.SetUniformf("CameraPosition", 0.0f, 20.0f, 50.0f);

	program2Tex.SetUniformI("DiffuseTexture", 0);
	program2Tex.SetUniformI("DiffuseTexture2", 1);
	program2Tex.SetUniformI("ShadowMap", 2);

	program2Tex.Desactivate();


	//Camaras
	_camera.SetPosition(0.0f, 20.0f, 50.0f);
	_lightCamera.SetPosition(0.0f, 20.0f, 0.0f);
	_lightCamera.Pitch(-90);
	_camera.Pitch(-20);
	_lightCamera.SetOrthographic(100.0f, 1.0f);

	_transform.SetScale(2, 2, 2);
	_transform.SetRotation(0.0f, 25.0f, 0.0f);
	_transform2.SetScale(30.0f, 0.5f, 30.0f);
	_transform2.SetPosition(0.0f, -15.0f, 0.0f);
	_transform2.SetRotation(0.0f, 0.0f, 0.0f);

	_myDephtbuffer.Create(2048);

}

void GameLoop()
{
	_transform.Rotate(0.05, -0.05f, 0.05f, false);

	_myDephtbuffer.Bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	program2.Activate();
	mat4 matModelo = _transform.GetModelMatrix();
	program2.SetUniformMatrix("mvpMatrix", _lightCamera.GetViewProjection() * matModelo);
	_mesh.Draw(GL_TRIANGLES);
	
	matModelo = _transform2.GetModelMatrix();
	program2.SetUniformMatrix("mvpMatrix", _lightCamera.GetViewProjection() * matModelo);

	_mesh.Draw(GL_TRIANGLES);

	program2.Desactivate();

	_myDephtbuffer.Unbind();
	glViewport(0, 0, 400, 400);

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program2Tex.Activate();

	glActiveTexture(GL_TEXTURE0);
	_back.Bind();
	glActiveTexture(GL_TEXTURE1);
	_logo.Bind();
	glActiveTexture(GL_TEXTURE2);
	_myDephtbuffer.BindDepthMap();
	matModelo = _transform.GetModelMatrix();
	mat3 normalMatrix = transpose(inverse(mat3(_transform.GetModelMatrix())));
	program2Tex.SetUniformMatrix("modelMatrix", matModelo);
	program2Tex.SetUniformMatrix3("normalMatrix", normalMatrix);
	program2Tex.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix());
	program2Tex.SetUniformMatrix("LightVPMatrix", _lightCamera.GetViewProjection());
	_mesh.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_back.Unbind();
	glActiveTexture(GL_TEXTURE1);
	_logo.Unbind();
	glActiveTexture(GL_TEXTURE2);
	_myDephtbuffer.UnbindDepthMap();
	program2Tex.Desactivate();

	program.Activate();
	glActiveTexture(GL_TEXTURE0);
	_floor.Bind();
	glActiveTexture(GL_TEXTURE2);
	_myDephtbuffer.BindDepthMap();
	matModelo = _transform2.GetModelMatrix();
	mat3 normalMatrix2 = transpose(inverse(mat3(_transform2.GetModelMatrix())));
	program.SetUniformMatrix("modelMatrix", matModelo);
	program.SetUniformMatrix3("normalMatrix", normalMatrix2);
	program.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform2.GetModelMatrix());
	program.SetUniformMatrix("LightVPMatrix", _lightCamera.GetViewProjection());

	_mesh.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_floor.Unbind();
	glActiveTexture(GL_TEXTURE2);
	_myDephtbuffer.UnbindDepthMap();
	program.Desactivate();

	//Cuando terminamos de renderear, cambiamp los buffers
	glutSwapBuffers();
}

void ReshapeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
}

void Idle()
{
	//Cuando opengl entra ne modo de reposo le decimos que vuelva a llamar el gameloop 
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
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