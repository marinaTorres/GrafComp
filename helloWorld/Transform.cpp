#include "Transform.h"

Transform::Transform(){
	_position = vec3(0.0f, 0.0f, 0.0f);
	_rotation = quat(vec3(0.0f, 0.0f, 0.0f));
	_scale = vec3(1.0f, 1.0f, 1.0f);

	_modelMatrix = mat4(1.0f);

	_forward = WORLD_FORWARD_VECTOR;
	_up = WORLD_UP_VECTOR;
	_right = WORLD_RIGHT_VECTOR;
}

mat4 Transform::GetModelMatrix(){
	return _modelMatrix;
}

vec3 Transform::GetPosition(){
	return _position;
}

quat Transform::GetRotation(){
	return _rotation;
}

vec3 Transform::GetScale(){
	return _scale;
}

void Transform::SetPosition(float x, float y, float z){
	_position = vec3(x, y, z);
	UpdateModelMatrixPosition();
}

void Transform::SetRotation(float x, float y, float z){
	_rotation = quat(radians(vec3(x, y, z)));
	UpdateModelMatrixRotationScale();
}

void Transform::SetScale(float x, float y, float z){
	_scale = vec3(x, y, z);
	UpdateModelMatrixRotationScale();
}

void Transform::MoveForward(float delta, bool world){
	if (world)	{
		_position += WORLD_FORWARD_VECTOR * delta;
	}else{
		_position += _forward * delta;
	}
	UpdateModelMatrixPosition();
}

void Transform::MoveUp(float delta, bool world){
	if (world){
		_position += WORLD_UP_VECTOR * delta;
	}else{
		_position += _up * delta;
	}
	UpdateModelMatrixPosition();
}

void Transform::MoveRight(float delta, bool world){
	if (world){
		_position += WORLD_RIGHT_VECTOR * delta;
	}else{
		_position += _right * delta;
	}
	UpdateModelMatrixPosition();
}

void Transform::Translate(float x, float y, float z, bool world){
	if (world){
		_position += vec3(x, y, z);
	}
	else{
		_position += _forward * z;
		_position += _up * y;
		_position += _right * x;
	}
}

void Transform::Rotate(float x, float y, float z, bool world){
	quat newRotation = quat(radians(vec3(x, y, z)));
	if (world){
		_rotation = newRotation * _rotation;
	}else{
		_rotation = _rotation * newRotation;
	}
	UpdateModelMatrixRotationScale();
}

void Transform::UpdateModelMatrixPosition(){
	_modelMatrix[3][0] = _position.x;
	_modelMatrix[3][1] = _position.y;
	_modelMatrix[3][2] = _position.z;
}

void Transform::UpdateModelMatrixRotationScale(){
	_modelMatrix = mat4_cast(_rotation);
	_modelMatrix[0] = _modelMatrix[0] * _scale.x;
	_modelMatrix[1] = _modelMatrix[1] * _scale.y;
	_modelMatrix[2] = _modelMatrix[2] * _scale.z;
	UpdateModelMatrixPosition();
	UpdateLocalVectors();
}

void Transform::UpdateLocalVectors(){
	mat4 rotationMatrix = mat4_cast(_rotation);
	_forward = vec3(rotationMatrix * vec4(WORLD_FORWARD_VECTOR, 0.0f));
	_up = vec3(rotationMatrix * vec4(WORLD_UP_VECTOR, 0.0f));
	_right = cross(_up, _forward);
}
