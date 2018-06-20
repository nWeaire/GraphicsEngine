#pragma once
#include "Camera.h"


class FlyCamera : public Camera
{
public:
	//-----------------------------------------------------
	// Default Constructor
	//-----------------------------------------------------
	FlyCamera();

	//-----------------------------------------------------
	// Default Destructor
	//-----------------------------------------------------
	~FlyCamera();

	//-----------------------------------------------------
	// Update function to call each frame
	// Parameters:
	//		float deltaTime: deltaTime value to use for updates
	//		float window: The instance of window
	//-----------------------------------------------------
	void Update(float deltatime, GLFWwindow* window);

	//-----------------------------------------------------
	// Sets Speed of camera
	// Parameters:
	//		float speed: speed to apply to camera
	//-----------------------------------------------------
	void setSpeed(float speed);

private:
	
	float m_speed;// Current speed of camera
	glm::vec3 m_up;

	double m_dMouseX; // Mouse x position
	double m_dMouseY; // Mouse y position

	double m_dDeltaMouseX; // Mouse delta x position
	double m_dDeltaMouseY; // Mouse delta y position
};

