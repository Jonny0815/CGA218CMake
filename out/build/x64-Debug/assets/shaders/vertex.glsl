#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colorRGB;

out vec3 colorVS;

uniform float dt;
uniform mat4 tmat;

void main(){
    
    colorVS = colorRGB;
    
    gl_Position = tmat * vec4(pos.x, pos.y, pos.z, 1.0);

}
