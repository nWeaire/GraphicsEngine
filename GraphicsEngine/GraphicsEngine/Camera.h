#pragma once
#include <glm.hpp>
#include <ext.hpp>
#include <glfw3.h>



class Camera
{
public:
	//-----------------------------------------------------
	// Default contructor
	//-----------------------------------------------------
	Camera();

	//-----------------------------------------------------
	// Default destructor
	//-----------------------------------------------------
	~Camera();

	//-----------------------------------------------------
	// Update function to call each frame
	// Parameters:
	//		float deltaTime: deltaTime value to use for updates
	//		float window: The instance of window
	//-----------------------------------------------------
	virtual void Update(float deltatime, GLFWwindow* window) = 0;

	//-----------------------------------------------------
	// Sets the perspective of the camera
	// Parameters:
	//		float fieldOfView: The degrees the camera can see
	//		float aspectRatio: The aspect ratio of the scene
	//		float near: The near float of the camera
	//		float far: The far float of the camera
	//-----------------------------------------------------
	void setPerspective(float fieldOfView, float aspectRatio, float near, float far);

	//-----------------------------------------------------
	// Sets where the camera is looking
	// Parameters:
	//		vector3 From: Position the camera is looking from
	//		Vector3 To: Position the camera is looking at
	//		Vector3 up: Position the camera
	//-----------------------------------------------------
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);

	// Sets the position of the camera
	// Parameters:
	//		vector3 position: The position to move the camera to 
	//-----------------------------------------------------
	void setPosition(glm::vec3 position);

	//-----------------------------------------------------
	// Gets the position in world space of the camera
	// Returns:
	//		Matrix4 WorldTransform: The position of the camera in world space
	//-----------------------------------------------------
	glm::mat4 getWorldTransform();

	//-----------------------------------------------------
	// Gets the view transform of the camera
	// Returns:
	//		Matrix4 viewTransform: The view transform of the camera
	//-----------------------------------------------------
	glm::mat4 getView();

	//-----------------------------------------------------
	// Gets the projection transform of the camera
	// Returns:
	//		Matrix4 projectionTransform: The projection transform of the camera
	//-----------------------------------------------------
	glm::mat4 getProjection();

	//-----------------------------------------------------
	// Gets the x view projection transform of the camera
	// Returns:
	//		Matrix4 view_x_projection: The x view projection transform of the camera
	//-----------------------------------------------------
	glm::mat4 getProjectionView();

protected:

	//-----------------------------------------------------
	// Updates the project view model of the camera
	//-----------------------------------------------------
	void updateProjectionViewTransform();

	glm::mat4 worldTransform;
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;
	glm::mat4 view_x_projection;
};

