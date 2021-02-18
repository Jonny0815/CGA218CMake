#version 330
in float lifetime; 
in vec2 uv; 
out vec4 color;  
uniform sampler2D matEmissive, matDiffuse, matSpecular;
void main(){
	vec4 col = vec4(texture(matEmissive,uv).rgb,1); 
	if(col.rgb == vec3(1.0)){
		discard; 
	}
	color = col; 
}