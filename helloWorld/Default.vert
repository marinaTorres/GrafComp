#version 330

in vec3 vertexPosition;
in vec3 vertexColor;

out vec3 InterpolatedColor;

void main(){
	InterpolatedColor=vertexColor;
	gl_Position=vec4(vertexPosition, 1.0f):

}