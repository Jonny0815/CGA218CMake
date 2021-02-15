#pragma once
#include "Transform.h"
#include "ShaderProgram.h"

using namespace std;

class Camera: public Transform {
public:
	Camera(int h_with, int h_height, float h_angle, float h_nearClippingPlane, float h_farClippingPlane);

	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);
	void render(ShaderProgram* shader);

	virtual glm::mat4 getViewMatrix();

protected:
	
	glm::mat4 getProjectionMatrix();
	void updateCameraVectors();


	int m_with = 0;
	int m_height = 0;
	float m_angle = 0.0;
	float m_nearClippingPlane = 0.0;
	float m_farClippingPlane = 0.0;
	float MouseSensitivity = 0.1f;
	float Yaw = -90.0f;
	float Pitch = 0.0f;
};