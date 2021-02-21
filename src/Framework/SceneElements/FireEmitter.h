#ifndef  FIRE_EMITTER_H
#define  FIRE_EMITTER_H
#include "PixelEmitter.h"
#include "ShaderProgram.h"
class FireEmitter : public PixelEmitter {
public: 
	FireEmitter(ShaderProgram *shader); 
	void render(ShaderProgram* shader, float dt, vec3 camPosition) override;

private: 
	ShaderProgram* m_shader; 
	class Particle
	{
	public: 
		vec3 position;
		float lifetime;
		float maxLifetime; 
		vec2 tex; 
		float cameradistance;
		bool operator<(const Particle& that) const {
			// Sort in reverse order : far particles drawn first.
			return this->cameradistance > that.cameradistance;
		}
	};
	const int particleCount = 200; 
	Particle particles[200];
	float positions[800];
	float colors[800];
	float texOffsetCords[400];
	float spriteWidth = 128; 
	float spriteHeight = 128;
	int sheetWidth = 1024; 
	int sheetHeight = 1024; 
	GLuint vertexBuffer;
	GLuint positionBuffer;
	GLuint vertexArray;
	GLuint TexBuffer; 
	GLuint TexOffsetBuffer; 
	GLuint colorBuffer; 
	vec3 startColor = vec3(1.0, 0.3, 0.0); 
	vec3 endColor = vec3(1.0); 
	void initializeEmitter();
	void draw();
	void update(float dt, vec3 camPosition);

};
#endif // ! FIRE_EMITTER_H
