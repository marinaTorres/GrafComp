#version 330

in vec3 InterpolatedColor;

out vec4 FragColor;

void main(){
	FragColor = vec4(InterpolatedColor, 1.0f);
	vec2 ppw = gl_FragCoord.xy;
	float d = sqrt((ppw[0]-200.0f)*(ppw[0]-200.0f)+(ppw[1]-200.0f)*(ppw[1]-200.0f));
    if(d<=150.0f){
    	discard;
		}
	}