#version 330

in vec3 VertexPosition;
in vec3 VertexColor;

out vec3 InterpolatedColor;
uniform mat4 mvplMatrix;

void main(){
	InterpolatedColor = VertexColor;
	gl_Position = mvplMatrix * vec4(VertexPosition, 1.0f);
}