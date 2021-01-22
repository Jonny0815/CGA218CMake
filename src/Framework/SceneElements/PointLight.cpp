#include "Transform.h"
#include "PointLight.h"

PointLight::PointLight(std::string h_name, glm::vec3 h_color, glm::vec3 h_pos)
{
	color = h_color;
	name = h_name;
	setPosition(h_pos);
}

void PointLight::bind(ShaderProgram* h_shader)
{
	shader = h_shader;
}

void PointLight::render()
{
	shader->setUniform("lightPos", getPosition());
	shader->setUniform("lightColor", color);
}
