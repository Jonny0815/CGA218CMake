#version 330
in vec3 Normal, LightDir, ViewDir;
uniform vec3 matDiffuse, lightColor;
uniform vec3 lightColorAmbient;
uniform vec3 matEmissive;
uniform mat3 matSpecular;
uniform float matShininess;
out vec4 color;  

void main() {
// normalize everything necessary // 
vec3 N = normalize(Normal);
vec3 L = normalize(LightDir);
// diffuse component //
float cosa = max(0.0, dot(N,L));
vec3 DiffuseTerm = matDiffuse * lightColor;   
color = vec4( DiffuseTerm * cosa, 1.0);
vec3 AmbientEmissiveTerm = matEmissive + matDiffuse * lightColorAmbient; 
color += vec4(AmbientEmissiveTerm, 0.0); 
vec3 V = normalize(ViewDir);
vec3 R = normalize(reflect(-L,N));
float cosBeta = max(0.0, dot(R,V));
float cosBetak = pow(cosBeta, matShininess);
vec3 SpecularTerm = matSpecular * lightColor;
vec3 FinalTerm = SpecularTerm * cosBetak;
//color += vec4(FinalTerm, 0.0); //tut nicht -> invalid operation
}
