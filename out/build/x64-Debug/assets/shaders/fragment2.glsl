#version 330
in vec3 Normal, LightDir, ViewDir;
in vec2 TextureCoor;
uniform vec3 lightColor;
uniform vec3 lightColorAmbient;
uniform sampler2D matEmissive, matDiffuse, matSpecular;
uniform float matShininess;
out vec4 color;  

void main() {

color = vec4(0.0, 1.0, 1.0, 0.0);
}