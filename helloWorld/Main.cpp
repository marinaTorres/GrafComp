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



//Animación
float rotateFingers = 0.05f;
float translateFingers = 0.004f;
int delta = 0;


//declaro shader program y mesh
ShaderProgram program;
ShaderProgram program2;
ShaderProgram program2Tex;
Mesh _meshPalm;
Mesh _meshFingers;

//Lo del transform
Transform _transformFloor;//Piso
Transform _transformPalm;//Palm
Transform _transformF1A;//Finger 1 bottom
Transform _transformF1B;//Finger 1 up
Transform _transformF2A;//Finger 2 bottom
Transform _transformF2B;//Finger 2 up
Transform _transformF3A;//Finger 3 bottom
Transform _transformF3B;//Finger 3 up
Transform _transformF4A;//Finger 4 bottom
Transform _transformF4B;//Finger 4 up


Camera _camera;
Camera _lightCamera;

//lo de la textura
Texture2D _back;
Texture2D _floor;
Texture2D _logo;

//el depth buffer
Dephtbuffer _myDephtbuffer;

void ReshapeWindow(int width, int height) {
	glViewport(0, 0, width, height);
}

vector <vec3> createPositions(float x, float y, float z) {
	vector<vec3> positions;
	//++++++++++++++++++++++Positions++++++++++++++++++++++\\
		//Cara Frontal
	positions.push_back(vec3(x, -y, z));//->0
	positions.push_back(vec3(x, y, z));//->1
	positions.push_back(vec3(-x, -y, z));//->2
	positions.push_back(vec3(-x, y, z));//->3

	//Cara Posterior
	positions.push_back(vec3(x, -y, -z));//->4
	positions.push_back(vec3(x, y, -z));//->5
	positions.push_back(vec3(-x, -y, -z));//->6
	positions.push_back(vec3(-x, y, -z));//->7

	//Cara Lateral Derecha
	positions.push_back(vec3(x, -y, -z));//->8
	positions.push_back(vec3(x, y, -z));//->9
	positions.push_back(vec3(x, -y, z));//->10
	positions.push_back(vec3(x, y, z));//->11

	//Cara Lateral Izquierda
	positions.push_back(vec3(-x, -y, -z));//->12
	positions.push_back(vec3(-x, y, -z));//->13
	positions.push_back(vec3(-x, -y, z));//->14
	positions.push_back(vec3(-x, y, z));//->15

	 //Cara Superior
	positions.push_back(vec3(x, y, z));//->16
	positions.push_back(vec3(x, y, -z));//->17
	positions.push_back(vec3(-x, y, z));//->18
	positions.push_back(vec3(-x, y, -z));//->19

	//Cara Inferior
	positions.push_back(vec3(x, -y, z));//->20
	positions.push_back(vec3(x, -y, -z));//->21
	positions.push_back(vec3(-x, -y, z));//->22
	positions.push_back(vec3(-x, -y, -z));//->23

	return positions;

}
void Initialize() {
	// Creando toda la memoria una sola vez al inicio de vida de mi programa
	// Vector de C++ es una lista de elementos, vector de glm es una matriz con muchos componentes
	// Lista de vec2
	// Claramente estamos trabajando en el CPU y RAM

	// Tantos colores por número de vertices tengas, si un vértice tiene un atributo, todos deben tenerlo
	// Arreglo de colors en el CPU

	vector<vec3> positionsFather= createPositions(13.0f,1.0f,13.0f);
	vector<vec3> positionsChild = createPositions(5.0f,1.0f,3.0f);
	vector<vec3> colors;
	vector<vec3> normals;
	vector<vec2> textures;
	//Cubo
	
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

	
	_meshPalm.CreateMesh(positionsFather.size());
	_meshPalm.SetPositionAttribute(positionsFather, GL_STATIC_DRAW, 0);
	_meshPalm.SetColorAttribute(colors, GL_STATIC_DRAW, 1);
	_meshPalm.SetNormalAttribute(normals, GL_STATIC_DRAW, 2);
	_meshPalm.SetTexCoordAttribute(textures, GL_STATIC_DRAW, 3);
	_meshPalm.SetIndices(indices, GL_STATIC_DRAW);

	_meshFingers.CreateMesh(positionsChild.size());
	_meshFingers.SetPositionAttribute(positionsChild, GL_STATIC_DRAW, 0);
	_meshFingers.SetColorAttribute(colors, GL_STATIC_DRAW, 1);
	_meshFingers.SetNormalAttribute(normals, GL_STATIC_DRAW, 2);
	_meshFingers.SetTexCoordAttribute(textures, GL_STATIC_DRAW, 3);
	_meshFingers.SetIndices(indices, GL_STATIC_DRAW);

	
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
	_camera.SetPosition(0.0f, 20.0f, 70.0f);
	_camera.Pitch(-20);
	_lightCamera.SetPosition(0.0f, 20.0f, 0.0f);
	_lightCamera.Pitch(-90);
	_lightCamera.SetOrthographic(100.0f, 1.0f);

	//Cubo padre
	_transformPalm.SetRotation(0.0f, 0.0f, 30.0f);
	

	//Cubo hijos
	//rotación pulgares
	_transformF1A.SetPosition(0.0f, 0.0f, 19.0f);
	_transformF1A.SetRotation(0.0f, 270.0f, 0.0f);
	_transformF1B.SetPosition(11.0f, 0.0f, 0.0f);
	
	_transformF2A.SetPosition(19.0f, 0.0f, 9.5f);
	_transformF2B.SetPosition(11.0f, 0.0f, 0.0f);
	
	_transformF3A.SetPosition(19.0f, 0.0f, 0.0f);
	_transformF3B.SetPosition(11.0f, 0.0f, 0.0f);
	
	_transformF4A.SetPosition(19.0f, 0.0f, -9.5f);
	_transformF4B.SetPosition(11.0f, 0.0f, 0.0f);

	//Piso
	_transformFloor.SetScale(30.0f, 0.5f, 30.0f);
	_transformFloor.SetPosition(0.0f, -15.0f, 0.0f);

	_myDephtbuffer.Create(2048);

}

void GameLoop(){
	
	_transformPalm.Rotate(0.05f, 0.05f, 0.0f, false);
	
	_transformF1A.Rotate(0.0f, 0.0f, rotateFingers, false);
	_transformF1A.Translate(0.0f, translateFingers, 0.0f, false);
	_transformF1B.Rotate(0.0f, 0.0f, rotateFingers, false);
	_transformF1B.Translate(0.0f, translateFingers, 0.0f, false);
	
	_transformF2A.Rotate(0.0f, 0.0f, rotateFingers, false);
	_transformF2A.Translate(0.0f, translateFingers, 0.0f, false);
	_transformF2B.Rotate(0.0f, 0.0f, rotateFingers, false);
	_transformF2B.Translate(0.0f, translateFingers, 0.0f, false);
	
	_transformF3A.Rotate(0.0f, 0.0f, rotateFingers, false);
	_transformF3A.Translate(0.0f, translateFingers, 0.0f, false);
	_transformF3B.Rotate(0.0f, 0.0f, rotateFingers, false);
	_transformF3B.Translate(0.0f, translateFingers, 0.0f, false);
	
	_transformF4A.Rotate(0.0f, 0.0f, rotateFingers, false);
	_transformF4A.Translate(0.0f, translateFingers, 0.0f, false);
	_transformF4B.Rotate(0.0f, 0.0f, rotateFingers, false);
	_transformF4B.Translate(0.0f, translateFingers, 0.0f, false);
	
	/*
	_transformF1A.Rotate(0.0f, 0.0f, rotateFingers, false);
	_transformF1B.Rotate(0.0f, 0.0f, rotateFingers, false);

	_transformF2A.Rotate(0.0f, 0.0f, rotateFingers, false);
	_transformF2B.Rotate(0.0f, 0.0f, rotateFingers, false);

	_transformF3A.Rotate(0.0f, 0.0f, rotateFingers, false);
	_transformF3B.Rotate(0.0f, 0.0f, rotateFingers, false);

	_transformF4A.Rotate(0.0f, 0.0f, rotateFingers, false);
	_transformF4B.Rotate(0.0f, 0.0f, rotateFingers, false);
	*/
	
	delta += 1;
	if (delta%2240==0) {
		rotateFingers = rotateFingers*-1.0 ;
		translateFingers = translateFingers*-1.0;
	}

	_myDephtbuffer.Bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Render de Sombras - 1er Render
	program2.Activate();
	//Piso
	program2.SetUniformMatrix("mvpMatrix", _lightCamera.GetViewProjection() * _transformFloor.GetModelMatrix());
	_meshPalm.Draw(GL_TRIANGLES);
	//Palma
	program2.SetUniformMatrix("mvpMatrix", _lightCamera.GetViewProjection() * _transformPalm.GetModelMatrix());
	_meshPalm.Draw(GL_TRIANGLES);
	//Fingers
	program2.SetUniformMatrix("mvpMatrix", _lightCamera.GetViewProjection()*_transformPalm.GetModelMatrix()* _transformF1A.GetModelMatrix());
	_meshFingers.Draw(GL_TRIANGLES);

	program2.SetUniformMatrix("mvpMatrix", _lightCamera.GetViewProjection()*_transformPalm.GetModelMatrix() *_transformF1A.GetModelMatrix()* _transformF1B.GetModelMatrix());
	_meshFingers.Draw(GL_TRIANGLES);


	program2.SetUniformMatrix("mvpMatrix", _lightCamera.GetViewProjection()*_transformPalm.GetModelMatrix()* _transformF2A.GetModelMatrix());
	_meshFingers.Draw(GL_TRIANGLES);

	program2.SetUniformMatrix("mvpMatrix", _lightCamera.GetViewProjection()*_transformPalm.GetModelMatrix()*_transformF2A.GetModelMatrix()* _transformF2B.GetModelMatrix());
	_meshFingers.Draw(GL_TRIANGLES);

	program2.SetUniformMatrix("mvpMatrix", _lightCamera.GetViewProjection()*_transformPalm.GetModelMatrix() * _transformF3A.GetModelMatrix());
	_meshFingers.Draw(GL_TRIANGLES);

	program2.SetUniformMatrix("mvpMatrix", _lightCamera.GetViewProjection()*_transformPalm.GetModelMatrix()*_transformF3A.GetModelMatrix()* _transformF3B.GetModelMatrix());
	_meshFingers.Draw(GL_TRIANGLES);

	program2.SetUniformMatrix("mvpMatrix", _lightCamera.GetViewProjection()*_transformPalm.GetModelMatrix()* _transformF4A.GetModelMatrix());
	_meshFingers.Draw(GL_TRIANGLES);

	program2.SetUniformMatrix("mvpMatrix", _lightCamera.GetViewProjection()*_transformPalm.GetModelMatrix()*_transformF4A.GetModelMatrix()* _transformF4B.GetModelMatrix());
	_meshFingers.Draw(GL_TRIANGLES);

	program2.Desactivate();

	_myDephtbuffer.Unbind();
	ReshapeWindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Render Camara
	program2Tex.Activate();

	glActiveTexture(GL_TEXTURE0);
	_back.Bind();
	glActiveTexture(GL_TEXTURE1);
	_logo.Bind();
	glActiveTexture(GL_TEXTURE2);
	_myDephtbuffer.BindDepthMap();

	//Palm
	program2Tex.SetUniformMatrix("modelMatrix", _transformPalm.GetModelMatrix());
	program2Tex.SetUniformMatrix3("normalMatrix", transpose(inverse(mat3(_transformPalm.GetModelMatrix()))));
	program2Tex.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transformPalm.GetModelMatrix());
	program2Tex.SetUniformMatrix("LightVPMatrix", _lightCamera.GetViewProjection());
	_meshPalm.Draw(GL_TRIANGLES);

	//Fingers
	program2Tex.SetUniformMatrix("modelMatrix", _transformPalm.GetModelMatrix() * _transformF1A.GetModelMatrix());
	program2Tex.SetUniformMatrix3("normalMatrix", transpose(inverse(mat3(_transformPalm.GetModelMatrix()*_transformF1A.GetModelMatrix()))));
	program2Tex.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_transformPalm.GetModelMatrix()* _transformF1A.GetModelMatrix());
	program2Tex.SetUniformMatrix("LightVPMatrix", _lightCamera.GetViewProjection());
	_meshFingers.Draw(GL_TRIANGLES);

	program2Tex.SetUniformMatrix("modelMatrix", _transformPalm.GetModelMatrix()* _transformF1A.GetModelMatrix() * _transformF1B.GetModelMatrix());
	program2Tex.SetUniformMatrix3("normalMatrix", transpose(inverse(mat3(_transformPalm.GetModelMatrix()*_transformF1A.GetModelMatrix()*_transformF1B.GetModelMatrix()))));
	program2Tex.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_transformPalm.GetModelMatrix()*_transformF1A.GetModelMatrix()* _transformF1B.GetModelMatrix());
	program2Tex.SetUniformMatrix("LightVPMatrix", _lightCamera.GetViewProjection());
	_meshFingers.Draw(GL_TRIANGLES);

	program2Tex.SetUniformMatrix("modelMatrix", _transformPalm.GetModelMatrix() * _transformF2A.GetModelMatrix());
	program2Tex.SetUniformMatrix3("normalMatrix", transpose(inverse(mat3(_transformPalm.GetModelMatrix()*_transformF2A.GetModelMatrix()))));
	program2Tex.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_transformPalm.GetModelMatrix()* _transformF2A.GetModelMatrix());
	program2Tex.SetUniformMatrix("LightVPMatrix", _lightCamera.GetViewProjection());
	_meshFingers.Draw(GL_TRIANGLES);

	program2Tex.SetUniformMatrix("modelMatrix", _transformPalm.GetModelMatrix()*_transformF2A.GetModelMatrix() * _transformF2B.GetModelMatrix());
	program2Tex.SetUniformMatrix3("normalMatrix", transpose(inverse(mat3(_transformPalm.GetModelMatrix()*_transformF2A.GetModelMatrix()*_transformF2B.GetModelMatrix()))));
	program2Tex.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_transformPalm.GetModelMatrix()*_transformF2A.GetModelMatrix()* _transformF2B.GetModelMatrix());
	program2Tex.SetUniformMatrix("LightVPMatrix", _lightCamera.GetViewProjection());
	_meshFingers.Draw(GL_TRIANGLES);

	program2Tex.SetUniformMatrix("modelMatrix", _transformPalm.GetModelMatrix()* _transformF3A.GetModelMatrix());
	program2Tex.SetUniformMatrix3("normalMatrix", transpose(inverse(mat3(_transformPalm.GetModelMatrix()*_transformF3A.GetModelMatrix()))));
	program2Tex.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() *_transformPalm.GetModelMatrix()* _transformF3A.GetModelMatrix());
	program2Tex.SetUniformMatrix("LightVPMatrix", _lightCamera.GetViewProjection());
	_meshFingers.Draw(GL_TRIANGLES);

	program2Tex.SetUniformMatrix("modelMatrix", _transformPalm.GetModelMatrix()* _transformF3A.GetModelMatrix() * _transformF3B.GetModelMatrix());
	program2Tex.SetUniformMatrix3("normalMatrix", transpose(inverse(mat3(_transformPalm.GetModelMatrix()*_transformF3A.GetModelMatrix()*_transformF3B.GetModelMatrix()))));
	program2Tex.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_transformPalm.GetModelMatrix()*_transformF3A.GetModelMatrix()* _transformF3B.GetModelMatrix());
	program2Tex.SetUniformMatrix("LightVPMatrix", _lightCamera.GetViewProjection());
	_meshFingers.Draw(GL_TRIANGLES);

	program2Tex.SetUniformMatrix("modelMatrix", _transformPalm.GetModelMatrix() * _transformF4A.GetModelMatrix());
	program2Tex.SetUniformMatrix3("normalMatrix", transpose(inverse(mat3(_transformPalm.GetModelMatrix()*_transformF4A.GetModelMatrix()))));
	program2Tex.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_transformPalm.GetModelMatrix()* _transformF4A.GetModelMatrix());
	program2Tex.SetUniformMatrix("LightVPMatrix", _lightCamera.GetViewProjection());
	_meshFingers.Draw(GL_TRIANGLES);
	
	program2Tex.SetUniformMatrix("modelMatrix", _transformPalm.GetModelMatrix()* _transformF4A.GetModelMatrix() * _transformF4B.GetModelMatrix());
	program2Tex.SetUniformMatrix3("normalMatrix", transpose(inverse(mat3(_transformPalm.GetModelMatrix()*_transformF4A.GetModelMatrix()*_transformF4B.GetModelMatrix()))));
	program2Tex.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()*_transformPalm.GetModelMatrix()*_transformF4A.GetModelMatrix()* _transformF4B.GetModelMatrix());
	program2Tex.SetUniformMatrix("LightVPMatrix", _lightCamera.GetViewProjection());
	_meshFingers.Draw(GL_TRIANGLES);

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
	
	mat3 normalMatrix2 = transpose(inverse(mat3(_transformFloor.GetModelMatrix())));
	program.SetUniformMatrix("modelMatrix", _transformFloor.GetModelMatrix());
	program.SetUniformMatrix3("normalMatrix", normalMatrix2);
	program.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transformFloor.GetModelMatrix());
	program.SetUniformMatrix("LightVPMatrix", _lightCamera.GetViewProjection());

	_meshPalm.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_floor.Unbind();
	glActiveTexture(GL_TEXTURE2);
	_myDephtbuffer.UnbindDepthMap();
	program.Desactivate();

	//Cuando terminamos de renderear, cambiamp los buffers
	glutSwapBuffers();
}



void Idle(){
	//Cuando opengl entra ne modo de reposo le decimos que vuelva a llamar el gameloop 
	glutPostRedisplay();
}

int main(int argc, char* argv[]){
	//inicializa freglut
	//este crea ventana
	//en donde se dibuja
	glutInit(&argc, argv);
	//INICIA EL CONTEXTO DE OPENGL; ESTO SON SUS CAPACIDADES GRAFICAS
	//En este caso se usa pipeline Programable
	glutInitContextProfile(GLUT_CORE_PROFILE);
	//SOLICITANDO VERSION 4.2 DE GL 
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