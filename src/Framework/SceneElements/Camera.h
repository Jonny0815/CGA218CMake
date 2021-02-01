#pragma once
#include "Transform.h"
#include "ShaderProgram.h"

using namespace std;

class Camera: public Transform {
public:
	Camera(int h_with, int h_height, float h_angle, float h_nearClippingPlane, float h_farClippingPlane);

	void render(ShaderProgram* shader);

protected:
	virtual glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	int m_with = 0;
	int m_height = 0;
	float m_angle = 0.0;
	float m_nearClippingPlane = 0.0;
	float m_farClippingPlane = 0.0;
};