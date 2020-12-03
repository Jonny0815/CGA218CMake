#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colorRGB;

out vec3 colorVS;

uniform float dt;

void main(){
    
   
	int t = int (dt*1000);

    if (t<1){
    colorVS = colorRGB;
    }else if(t>4){
    colorVS = vec3(0.5,0.0,1.0);
    }else {
    colorVS = vec3(1.0,0.0,0.0);
    }

    
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);

}
