#include "Camera.h"

Camera::Camera(int h_with, int h_height, float h_angle, float h_nearClippingPlane, float h_farClippingPlane)
{
	m_with = h_with;
	m_height = h_height;
	m_angle = h_angle;
	m_nearClippingPlane = h_nearClippingPlane;
	m_farClippingPlane = h_farClippingPlane;
}

//glm::mat4 Camera::getViewMatrix()
//{
//	glm::vec3 position;
//	glm::vec3 lookatpos;
//
//	if (getParent() != nullptr)
//	{
//		position = getParent()->getPosition() + getPosition();
//		lookatpos = getParent()->getPosition();
//	}
//	else {
//
//		position = getPosition();
//		lookatpos = getPosition() - getDirection();
//	}
//
//	return glm::lookAt(position, lookatpos, getYAxis());
//}

glm::mat4 Camera::getViewMatrix()
{
	return glm::mat4();
}

glm::mat4 Camera::getProjectionMatrix()
{
	float aspect = m_with / m_height;
	return glm::perspective(m_angle, aspect, m_nearClippingPlane, m_farClippingPlane);
}

void Camera::render(ShaderProgram* shader)
{
	shader->setUniform("view", getViewMatrix(), false);
	shader->setUniform("projection", getProjectionMatrix(), false);

}
