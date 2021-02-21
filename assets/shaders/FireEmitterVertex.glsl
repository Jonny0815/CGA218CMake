#version 330
layout (location = 0) in vec3 vertex_position; 
layout (location = 10) in vec4 position; 
layout (location = 11) in vec2 texCoords; 
layout (location = 12) in vec4 col; 
layout (location = 13) in vec2 texOffset; 

uniform mat4 view; 
uniform mat4 projection;
uniform mat4 model; 
uniform float particleSize;
uniform float heightFactor; 
uniform float widthFactor; 
 
out float lifetime; 
out vec4 pColor; 
out vec2 uv; 
void main(){
	vec4 positionViewSpace = view * model * vec4(position.xyz,1); 
	positionViewSpace.xy += particleSize * (vertex_position.xy - vec2(0.5)); 
	//positionViewSpace.xy += particleSize * (vertex_position.xy); 
	gl_Position = projection *positionViewSpace; 
	pColor = col; 
	lifetime = position.w; 
	uv = vec2(texCoords.x + widthFactor * texOffset.x,texCoords.y + heightFactor * texOffset.y);
}