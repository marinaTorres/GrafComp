#version 330

in vec3 InterpolatedColor;

out vec4 FragColor;

//esto es la resolucion de la ventana en pixeles
uniform vec2 Resolution;

void main(){
	FragColor = vec4(InterpolatedColor, 1.0f);
	//vec2 ppw = gl_FragCoord.xy;
	//float d = sqrt((ppw[0]-200.0f)*(ppw[0]-200.0f)+(ppw[1]-200.0f)*(ppw[1]-200.0f));
    //if(d<=100.0f){
    	//discard;
		//}

	
	//es la posición del pixel en la ventana en 
	//un rango de [(0,0),(1,1)]
	vec2 p = gl_FragCoord.xy/Resolution;
	//Calculando un vector que va del pixel al 
	//centro de la ventana
	vec2 q = p-vec2(0.5f,0.5f);
	//si el vector que tiene una medida menor a 0.25,
	//descartamos el pixel
	if(length(q)<0.25){
		discard;
	}
}