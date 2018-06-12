#include "Camera.h"



Camera::Camera()
{
	viewTransform = glm::mat4(1);
	worldTransform = glm::mat4(1);
	projectionTransform = glm::mat4(1);

}


Camera::~Camera()
{
}

void Camera::setPerspective(float fieldOfView, float aspectRatio, float near, float far)
{
	//Sets Projection Transform
	projectionTransform = glm::perspective(glm::pi<float>() * fieldOfView, aspectRatio, near, far);

	//Update ViewProjection
	updateProjectionViewTransform();
}

void Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	//Sets View Transform
	viewTransform = glm::lookAt(from,to,up);
	worldTransform = glm::inverse(viewTransform);
	//Update ViewProjection
	updateProjectionViewTransform();
}

void Camera::setPosition(glm::vec3 position)
{
	//Sets position of the world transform
	worldTransform[3] = glm::vec4(position,1);

	//Inverses World Transform
	viewTransform = glm::inverse(worldTransform);

	//Update ViewProjection
	updateProjectionViewTransform();
}

glm::mat4 Camera::getWorldTransform()
{
	//Returns World Transform
	return worldTransform;
}

glm::mat4 Camera::getView()
{
	//Returns View Transform
	return viewTransform;
}

glm::mat4 Camera::getProjection()
{
	//Returns Projection Transform
	return projectionTransform;
}

glm::mat4 Camera::getProjectionView()
{
	//Multiplys Projection Transform and View Transform
	return view_x_projection;
}

void Camera::updateProjectionViewTransform()
{
	//Update ViewProjection
	view_x_projection = projectionTransform * viewTransform;
}
