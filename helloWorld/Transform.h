#pragma once 
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

using namespace glm;

class Transform {
public:
	Transform();

	mat4 GetModelMatrix();
	vec3 GetPosition();
	quat getRotation();
	vec3 GetScale();

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);

	void Translate(float x, float y, float z, bool world);
	void MoveFoward(float delta, bool world);
	void MoveUP(float delta, bool world);
	void MoveRight(float delta, bool world);
	void Rotate(float x, float y, float z, bool world);

	static constexpr vec3 WORLD_FOWARD_VECTOR = vec3(0.0f, 0.0f, 1.0f);
	static constexpr vec3 WORLD_UP_VECTOR = vec3(0.0f, 1.0f, 0.0f);
	static constexpr vec3 WORLD_RIGHT_VECTOR = vec3(1.0f, 0.0f, 0.0f);

private:
	void UpdateLocalVector();
	void UpdateModelMatrixPosition();
	void UpdateModelMatrixRotationScale();

	mat4 _modelMatrix;
	
	vec3 _position;
	
	quat _rotation;
	vec3 _scale;

	vec3 _foward;
	vec3 _up;
	vec3 _right;
};

