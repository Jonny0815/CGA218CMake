#include "FireEmitter.h"
#include <time.h>
FireEmitter::FireEmitter(ShaderProgram* shader)
{
	m_shader = shader; 
	srand(time(NULL)); 
	initializeEmitter(); 
}

void FireEmitter::render(ShaderProgram* shader, float dt, vec3 camPosition)
{
	if (m_shader->prog == shader->prog)
	{
		update(dt,camPosition);
		m_shader->setUniform("particleSize",0.3f);
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
		shader->setUniform("heightFactor", spriteHeight / sheetHeight); 
		shader->setUniform("widthFactor", spriteWidth / sheetWidth); 
		draw();
	}
}

void FireEmitter::initializeEmitter()
{
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
	//upload positions
	float x = 0, y = 0;
	sheetHeight = 1024;
	sheetWidth = sheetHeight;
	spriteHeight = sheetHeight / 8;
	spriteWidth = spriteHeight;
	std::vector< float > tex = {

			(x * spriteWidth) / sheetWidth,(y * spriteWidth) / sheetWidth,
			((x + 1) * spriteWidth) / sheetWidth,(y * spriteWidth) / sheetWidth,
			(x * spriteWidth) / sheetWidth,((y + 1) * spriteWidth) / sheetWidth,
			((x + 1) * spriteWidth) / sheetWidth,((y + 1) * spriteWidth) / sheetWidth,

	};


	//positions
	//this->particles.resize(100);
	for (uint i = 0; i < particleCount; ++i)
	{
		// give every particle a random position
		this->particles[i].position = randomBetween(vec3(0.0f), vec3(0.3f, 0.2f, 0.4f));
		this->particles[i].lifetime = randomBetween(1.0f, 2.0f);
		this->particles[i].maxLifetime = this->particles[i].lifetime;
		this->particles[i].cameradistance = -1.0;
	}
	//upload texCoords
	glGenBuffers(1, &TexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, TexBuffer);
	glBufferData(GL_ARRAY_BUFFER, tex.size() * sizeof(float), tex.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(11);
	glVertexAttribPointer(11, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//upload positions
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, particleCount * 4 * sizeof(float), this->positions, GL_STREAM_DRAW);
	glEnableVertexAttribArray(10);
	glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glVertexAttribDivisor(10, 1);

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, particleCount * 4 * sizeof(float), this->colors, GL_STREAM_DRAW);
	glEnableVertexAttribArray(12);
	glVertexAttribPointer(12, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glVertexAttribDivisor(12, 1);

	glGenBuffers(1, &TexOffsetBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->TexOffsetBuffer);
	glBufferData(GL_ARRAY_BUFFER, particleCount * 2 * sizeof(float), this->colors, GL_STREAM_DRAW);
	glEnableVertexAttribArray(13);
	glVertexAttribPointer(13, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glVertexAttribDivisor(13, 1);


}

void FireEmitter::draw()
{
	//update pos buffer
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, particleCount * 4 * sizeof(float), positions);
	glBindBuffer(GL_ARRAY_BUFFER, TexOffsetBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, particleCount * 2 * sizeof(float), texOffsetCords);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, particleCount * 4 * sizeof(float), colors);
	//exchangeBuffers(); 
	//va
	glBindVertexArray(vertexArray);
	glVertexAttribDivisor(10, 1);
	//glVertexAttribDivisor(11, 4);
	glVertexAttribDivisor(12, 1);
	glVertexAttribDivisor(13, 1);
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, particleCount);

}

void FireEmitter::update(float dt, vec3 camPosition)
{
	for (uint i = 0; i < particleCount; ++i)
	{
		// subtract from the particles lifetime
		this->particles[i].lifetime -= dt;

		float x = 0, y = 0;
		// if the lifetime is below 0 respawn the particle
		if (this->particles[i].lifetime <= 0.0f)
		{
			this->particles[i].position = randomBetween(vec3(0.0f), vec3(0.3f,0.2f,0.4f));
			this->particles[i].lifetime = randomBetween(1.0f, 2.0f);
			this->particles[i].maxLifetime = this->particles[i].lifetime;
			this->particles[i].cameradistance = glm::length2(this->particles[i].position - camPosition); 
			std::sort(&particles[0], &particles[particleCount]);

		}
		
		// move the particle up depending on the delta time
		this->particles[i].position += vec3(0.0f, dt/2, 0.0f);

		// update the position buffer
		this->positions[i * 4 + 0] = this->particles[i].position[0];
		this->positions[i * 4 + 1] = this->particles[i].position[1];
		this->positions[i * 4 + 2] = this->particles[i].position[2];
		this->positions[i * 4 + 3] = this->particles[i].lifetime;

		float t = this->particles[i].lifetime / this->particles[i].maxLifetime; 
		this->colors[i * 4 + 0] = endColor.x + (startColor.x - endColor.x) * t;
		this->colors[i * 4 + 1] = endColor.y + (startColor.y - endColor.y) * t;
		this->colors[i * 4 + 2] = endColor.z + (startColor.z - endColor.z) * t;
		this->colors[i * 4 + 3] = 1.0;

		//compute sprite index depending on lifetime
		float mc = this->particles[i].lifetime / this->particles[i].maxLifetime; 
		int z = mc * (8 * 8); 
		int yn = z / 8; 
		x = z - (yn * 8); 
		y = 8 - float(yn); 
		
		this->texOffsetCords[i * 2 + 0] = x;
		this->texOffsetCords[i * 2 + 1] = y;

	}

}
