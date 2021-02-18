#version 330
layout (location = 0) in vec3 vertex_position; 
layout (location = 10) in vec4 position; 


uniform mat4 view; 
uniform mat4 projection;
uniform mat4 model; 
uniform float particleSize; 
out float lifetime; 
out vec2 uv; 
void main(){
	vec4 positionViewSpace = view * model * vec4(position.xyz,1); 
	positionViewSpace.xy += particleSize * (vertex_position.xy - vec2(0.5)); 
	gl_Position = projection *positionViewSpace; 
	//gl_Position = vec4(vertex_position.xyz,1); 
	lifetime = position.w; 
	uv = vec2(vertex_position.x,vertex_position.y); 
}