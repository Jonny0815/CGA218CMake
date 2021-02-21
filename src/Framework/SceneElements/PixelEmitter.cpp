#include "PixelEmitter.h"
#include <time.h>
#include <math.h>

PixelEmitter::PixelEmitter()
{
}

PixelEmitter::PixelEmitter( ShaderProgram* shader)
{
	srand(time(NULL));
	m_shader = shader;
	initializeEmitter();

}

void PixelEmitter::update(float dt)
{
	for (uint i = 0; i < this->particles.size(); ++i)
	{
		// subtract from the particles lifetime
		this->particles[i].lifetime -= dt/2;

		// if the lifetime is below 0 respawn the particle
		if (this->particles[i].lifetime <= 0.0f)
		{
			this->particles[i].position = randomBetween(vec3(-1.0f), vec3(1.0f));
			this->particles[i].lifetime = randomBetween(3.0f, 4.0f);
			//this->particles[i].position = vec3(1.0f);
			//this->particles[i].lifetime = 1.5f;
		}

		// move the particle down depending on the delta time
		//this->particles[i].position -= vec3(0.0f, dt * 2.0f, 0.0f);
		//this->particles[i].position -= vec3(0.0f, dt, 0.0f);
		this->particles[i].position -= vec3(0.0 + sin(particles[i].lifetime)*0.002, dt, 0.0 + cos(particles[i].lifetime)*0.0015);

		// update the position buffer
		this->positions[i * 4 + 0] = this->particles[i].position[0];
		this->positions[i * 4 + 1] = this->particles[i].position[1];
		this->positions[i * 4 + 2] = this->particles[i].position[2];
		this->positions[i * 4 + 3] = this->particles[i].lifetime;
	}

}

void PixelEmitter::draw()
{
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(10);
	//
	//update pos buffer
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, particles.size() * 4 * sizeof(float), positions);
	//exchangeBuffers(); 
	//va
	glBindVertexArray(vertexArray); 
	glVertexAttribDivisor(10, 1);
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, this->particles.size());
	
	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(10);


}
void PixelEmitter::render(ShaderProgram* shader, float dt)
{
	
	if (m_shader->prog == shader->prog)
	{
		update(dt);
		m_shader->setUniform("particleSize", 0.2f);
		if (materialSet) {
			_mat.render();
		}
		glm::mat4 parentMat(1.0);
		Transform* akt = this;
		while (akt->getParent() != nullptr)
		{
			akt = akt->getParent();
			parentMat = akt->getTransformMatrix() * parentMat;
		}
		glm::mat4 tM = getTransformMatrix();
		shader->setUniform("model", parentMat * getTransformMatrix(), false);
		draw();
	}
}

void PixelEmitter::setMaterial(Material mat)
{
	_mat = mat; 
	materialSet = true;
}

vec3 PixelEmitter::randomBetween(vec3 lowerBound, vec3 higherBound)
{
	float x = randomBetween(lowerBound.x, higherBound.x);
	float y = randomBetween(lowerBound.y, higherBound.y);
	float z = randomBetween(lowerBound.z, higherBound.z);
	return vec3(x, y, z);
}

//todo 
float PixelEmitter::randomBetween(float lowerBound, float higherBound)
{
	float range = higherBound - lowerBound;
	float i = (rand() % 2000 - 1000.0f) / 1000.0f; 
	return i;
}

void PixelEmitter::initializeEmitter()
{
	// fill the vertex buffer
	std::vector< float > vertices;
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	vertices.push_back(1.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	vertices.push_back(0.0f);
	vertices.push_back(1.0f);
	vertices.push_back(0.0f);

	vertices.push_back(1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(0.0f);
	//upload vertecies 
	glGenBuffers(1, &vertexBuffer);
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//positions
	this->particles.resize(100);
	for (uint i = 0; i < this->particles.size(); ++i)
	{
		// give every particle a random position
		this->particles[i].position = randomBetween(vec3(-1.0f), vec3(1.0f));
		this->particles[i].lifetime = randomBetween(1.0f, 2.0f);
	}
	//upload positions
	glGenBuffers(1, &positionBuffer);
	//glGenVertexArrays(1, &vertexArray);
	//glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, this->positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->particles.size() * 4 * sizeof(float), this->positions, GL_STREAM_DRAW);
	glEnableVertexAttribArray(10);
	glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glVertexAttribDivisor(10, 1);
	// fill the position buffer
	//glBindBuffer(GL_ARRAY_BUFFER, this->positionBuffer);
	//glBufferData(GL_ARRAY_BUFFER, this->particles.size() * 4 * sizeof(float), this->positions, GL_STREAM_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, this->particles.size() * 4 * sizeof(float), this->positions, GL_DYNAMIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
}