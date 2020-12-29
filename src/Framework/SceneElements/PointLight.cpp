#include "Transform.h"
#include "PointLight.h"

PointLight::PointLight(std::string h_name, glm::vec3 h_color, glm::vec3 h_pos, glm::vec3 h_direction)
{
	color = h_color;
	name = h_name;
	setPosition(h_pos);
	//TODO direction
}

void PointLight::bind(ShaderProgram* h_shader)
{
	shader = h_shader;
}

void PointLight::render()
{
	//shader->use();

}
