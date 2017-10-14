#pragma once

#include <glm/glm.hpp>
#include "Transform.h"

using namespace glm;
using namespace std;

class Camera {
public:
	Camera();
	mat4 GetViewProjection();
	mat4 GetViewMatrix();
	mat4 GetProjectionMatrix();
	vec3 GetPosition();

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	void MoveForward(float delta, bool worl = false);
	void MoveUp(float delta, bool worl = false);
	void MoveRight(float delta, bool worl = false);

	//Rota en el eje Y
	void Yaw(float degrees);
	//Rota en el eje z
	void Roll(float degrees);
	//Rot en el eje X
	void Pitch(float degrees);
	void Rotate(float x, float y, float z, bool worl = false);

	//Que tan cerca y que tan lejos va a ver en el plano del corte,
	//
	void SetPerspective(float nearPlane, float farPlane, float fieldOfView, float aspectRatio);
	void SetOrthographic(float sixe, float aspectRatio);

private:
	Transform _transform;

	mat4 _viewMatrix;
	mat4 _projectionMatrix;

};