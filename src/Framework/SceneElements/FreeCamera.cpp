#include "FreeCamera.h"

FreeCamera::FreeCamera(int h_with, int h_height, float h_angle, float h_nearClippingPlane, float h_farClippingPlane):
	Camera(h_with, h_height, h_angle, h_nearClippingPlane, h_farClippingPlane)
{
	
}

glm::mat4 FreeCamera::getViewMatrix()
{
	return glm::lookAt(getPosition(), getPosition() - getDirection(), getYAxis());
}


