#include "FlyCamera.h"



FlyCamera::FlyCamera() : Camera()
{
	m_speed = 10;
}


FlyCamera::~FlyCamera()
{
}

void FlyCamera::Update(float deltatime, GLFWwindow* window)
{
	//Calculate delta XY of mouse
	glfwGetCursorPos(window, &m_dMouseX, &m_dMouseY);

	////Radians to degress
	m_dDeltaMouseX = (720 - m_dMouseX) * 0.0174533;
	m_dDeltaMouseY = (450 - m_dMouseY) * 0.0174533;

	////Keep mouse locked to screen
	glfwSetCursorPos(window, 720, 450);

	////Calculate relative world up
	glm::vec4 up = glm::inverse(worldTransform) * glm::vec4(0, 1, 0, 0);
	glm::mat4 rotMat(1.0f);

	////Rotate around world up
	rotMat = glm::rotate((float)-m_dDeltaMouseX * deltatime, glm::vec3(up[0], up[1], up[2]));
	viewTransform = rotMat * viewTransform;

	////Rotate up down
	rotMat = glm::rotate((float)-m_dDeltaMouseY * deltatime, glm::vec3(1, 0, 0));
	viewTransform = rotMat * viewTransform;

	////Update world transform
	worldTransform = glm::inverse(viewTransform);

	

	if (glfwGetKey(window, GLFW_KEY_W))
	{
		worldTransform[3] += worldTransform[2] * deltatime * -m_speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		worldTransform[3] += worldTransform[2] * deltatime * m_speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		worldTransform[3] += worldTransform[0] * deltatime * -m_speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		worldTransform[3] += worldTransform[0] * deltatime * m_speed;
	}

	worldTransform[3][3] = 1.0f;
	viewTransform = glm::inverse(worldTransform);
	updateProjectionViewTransform();
}

void FlyCamera::setSpeed(float speed)
{
	speed = m_speed;
}
