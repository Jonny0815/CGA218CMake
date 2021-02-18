#ifndef PIXEL_EMITTER_H
#define PIXEL_EMITTER_H
#include "Camera.h"
#include "Transform.h"
#include <ShaderProgram.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include "Material.h"
using namespace glm; 
class PixelEmitter : public Transform{
public: 
	PixelEmitter(); 
	PixelEmitter(ShaderProgram * shader); 
	void virtual render(ShaderProgram * shader, float dt);
	void setMaterial(Material mat);
	void draw();
	void update(float dt);
protected: 
	struct Particle
	{
		vec3 position;
		float lifetime;
	};
	
	vec3 randomBetween(vec3 lowerBound, vec3 higherBound); 
	float randomBetween(float lowerBound, float higherBound); 

	std::vector<Particle> particles;
	float positions[400];
	GLuint vertexBuffer;
	GLuint positionBuffer;
	GLuint vertexArray; 
	//Gluint billboard_vertex_buffer; 
	void initializeEmitter(); 
	ShaderProgram* m_shader; 
	bool materialSet = false; 
	Material _mat; 
};


#endif