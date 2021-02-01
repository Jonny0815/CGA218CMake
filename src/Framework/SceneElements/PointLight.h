#include "Transform.h"
#include <ShaderProgram.h>

class PointLight : public Transform {
public:

	PointLight(std::string h_name, glm::vec3 h_color, glm::vec3 h_pos);

	void render(ShaderProgram* shader);

private:

	glm::vec3 color;
	std::string name;

};