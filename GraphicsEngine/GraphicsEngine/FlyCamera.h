#pragma once
#include "Camera.h"


class FlyCamera : public Camera
{
public:
	FlyCamera();
	~FlyCamera();
	void Update(float deltatime, GLFWwindow* window);
	void setSpeed(float speed);

private:
	float m_speed;
	glm::vec3 m_up;

	double m_dMouseX;
	double m_dMouseY;

	double m_dDeltaMouseX;
	double m_dDeltaMouseY;
};

