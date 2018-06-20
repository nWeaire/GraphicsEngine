#include "FlyCamera.h"


//-----------------------------------------------------
// Default Constructor
//-----------------------------------------------------
FlyCamera::FlyCamera() : Camera()
{
	m_speed = 10;
}

//-----------------------------------------------------
// Default Destructor
//-----------------------------------------------------
FlyCamera::~FlyCamera()
{
}

//-----------------------------------------------------
// Update function to call each frame
// Parameters:
//		float deltaTime: deltaTime value to use for updates
//		float window: The instance of window
//-----------------------------------------------------
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

	

	if (glfwGetKey(window, GLFW_KEY_W)) // If pressing W key
	{
		worldTransform[3] += worldTransform[2] * deltatime * -m_speed; // Apply forward motion
	}
	if (glfwGetKey(window, GLFW_KEY_S)) // If pressing S key 
	{
		worldTransform[3] += worldTransform[2] * deltatime * m_speed; // Apply backwards motion
	}
	if (glfwGetKey(window, GLFW_KEY_A)) // If pressing A key
	{
		worldTransform[3] += worldTransform[0] * deltatime * -m_speed; // Apply motion to the left
	}
	if (glfwGetKey(window, GLFW_KEY_D)) // If pressing D key
	{
		worldTransform[3] += worldTransform[0] * deltatime * m_speed; // Apply motion to the right
	}

	worldTransform[3][3] = 1.0f; // Sets world transform
	viewTransform = glm::inverse(worldTransform); // Inverses world transform for view transform
	updateProjectionViewTransform(); // Update project view model 
}

//-----------------------------------------------------
// Sets Speed of camera
// Parameters:
//		float speed: speed to apply to camera
//-----------------------------------------------------
void FlyCamera::setSpeed(float speed)
{
	speed = m_speed; // Sets cameras speed
}
