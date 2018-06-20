#include "Camera.h"


//-----------------------------------------------------
// Default Constructor
//-----------------------------------------------------
Camera::Camera()
{
	viewTransform = glm::mat4(1);
	worldTransform = glm::mat4(1);
	projectionTransform = glm::mat4(1);

}

//-----------------------------------------------------
// Default Destructor
//-----------------------------------------------------
Camera::~Camera()
{
}

//-----------------------------------------------------
// Sets the perspective of the camera
// Parameters:
//		float fieldOfView: The degrees the camera can see
//		float aspectRatio: The aspect ratio of the scene
//		float near: The near float of the camera
//		float far: The far float of the camera
//-----------------------------------------------------
void Camera::setPerspective(float fieldOfView, float aspectRatio, float near, float far)
{
	//Sets Projection Transform
	projectionTransform = glm::perspective(glm::pi<float>() * fieldOfView, aspectRatio, near, far);

	//Update ViewProjection
	updateProjectionViewTransform();
}

//-----------------------------------------------------
// Sets where the camera is looking
// Parameters:
//		vector3 From: Position the camera is looking from
//		Vector3 To: Position the camera is looking at
//		Vector3 up: Position the camera
//-----------------------------------------------------
void Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	//Sets View Transform
	viewTransform = glm::lookAt(from,to,up);
	worldTransform = glm::inverse(viewTransform);
	//Update ViewProjection
	updateProjectionViewTransform();
}

//-----------------------------------------------------
// Sets the position of the camera
// Parameters:
//		vector3 position: The position to move the camera to 
//-----------------------------------------------------
void Camera::setPosition(glm::vec3 position)
{
	//Sets position of the world transform
	worldTransform[3] = glm::vec4(position,1);

	//Inverses World Transform
	viewTransform = glm::inverse(worldTransform);

	//Update ViewProjection
	updateProjectionViewTransform();
}

//-----------------------------------------------------
// Gets the position in world space of the camera
// Returns:
//		Matrix4 WorldTransform: The position of the camera in world space
//-----------------------------------------------------
glm::mat4 Camera::getWorldTransform()
{
	//Returns World Transform
	return worldTransform;
}

//-----------------------------------------------------
// Gets the view transform of the camera
// Returns:
//		Matrix4 viewTransform: The view transform of the camera
//-----------------------------------------------------
glm::mat4 Camera::getView()
{
	//Returns View Transform
	return viewTransform;
}

//-----------------------------------------------------
// Gets the projection transform of the camera
// Returns:
//		Matrix4 projectionTransform: The projection transform of the camera
//-----------------------------------------------------
glm::mat4 Camera::getProjection()
{
	//Returns Projection Transform
	return projectionTransform;
}

//-----------------------------------------------------
// Gets the x view projection transform of the camera
// Returns:
//		Matrix4 view_x_projection: The x view projection transform of the camera
//-----------------------------------------------------
glm::mat4 Camera::getProjectionView()
{
	//Multiplys Projection Transform and View Transform
	return view_x_projection;
}

//-----------------------------------------------------
// Updates the project view model of the camera
//-----------------------------------------------------
void Camera::updateProjectionViewTransform()
{
	//Update ViewProjection
	view_x_projection = projectionTransform * viewTransform;
}
