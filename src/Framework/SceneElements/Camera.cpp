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

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    lookinto(front);
    //Front = glm::normalize(front);
    //// also re-calculate the Right and Up vector
    //Right = glm::normalize(glm::cross(Front, glm::vec3(0.0f, 1.0f, 0.0f)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    //Up = glm::normalize(glm::cross(Right, Front));
}