#include "Camera.h"

class FreeCamera : public Camera {
public:
	FreeCamera(int h_with, int h_height, float h_angle, float h_nearClippingPlane, float h_farClippingPlane);

	glm::mat4 getViewMatrix() override;
private:
	
	

};