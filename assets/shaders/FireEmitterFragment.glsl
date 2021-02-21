#version 330
in float lifetime; 
in vec2 uv; 
out vec4 color;  
uniform sampler2D matEmissive, matDiffuse, matSpecular;
in vec4 pColor; 
void main(){
	vec4 col = texture(matEmissive,uv); 
	color = col;
	vec4 finalCol = pColor; 
	//finalCol.w *= col.a;
	//color =  finalCol ; 
	//color = vec4(uv.x,uv.y,0,1.0); 
}