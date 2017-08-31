#version 330

in vec3 InterpolatedColor;

out vec4 fragColor;


void main(){
	fragColor=vec4(InterpolatedColor,1.0f);
}