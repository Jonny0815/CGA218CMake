#include "Transform.h"
#include <ShaderProgram.h>

class PointLight : public Transform {
public:

	PointLight(std::string h_name, glm::vec3 h_color, glm::vec3 h_pos);

	void bind(ShaderProgram* h_shader);
	void render();

private:

	glm::vec3 color;
	std::string name;

	ShaderProgram* shader;

};