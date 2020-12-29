#include "ThirdPersonCamera.h"

ThirdPersonCamera::ThirdPersonCamera(int h_with, int h_height, float h_angle, float h_nearClippingPlane, float h_farClippingPlane):
	Camera(h_with, h_height, h_angle, h_nearClippingPlane, h_farClippingPlane)
{

}

glm::mat4 ThirdPersonCamera::getViewMatrix()
{
	glm::vec3 position;
	glm::vec3 lookatpos;

	if (getParent() != nullptr)
	{
		position = getParent()->getPosition() - glm::vec3(4,4,4) * getParent()->getZAxis() + glm::vec3(1.3,1.3,1.3) * getYAxis();

		lookatpos = getParent()->getPosition();
	}
	else {

		position = getPosition();
		lookatpos = getPosition() - getDirection();
	}

	return glm::lookAt(position, lookatpos, getYAxis());
}