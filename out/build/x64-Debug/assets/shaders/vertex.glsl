#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colorRGB;

out vec3 colorVS;

uniform float dt;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 ambientlight;

void main(){
    
    colorVS = colorRGB * ambientlight;
    
    gl_Position = projection * view * model * vec4(pos.x, pos.y, pos.z, 1.0);

}