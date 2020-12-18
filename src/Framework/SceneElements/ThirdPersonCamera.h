#include "Camera.h"

class ThirdPersonCamera : public Camera {
public:
	ThirdPersonCamera(int h_with, int h_height, float h_angle, float h_nearClippingPlane, float h_farClippingPlane);
private:
	glm::mat4 getViewMatrix();
};