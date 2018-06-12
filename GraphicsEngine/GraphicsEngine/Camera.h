#pragma once
#include <glm.hpp>
#include <ext.hpp>
#include <glfw3.h>



class Camera
{
public:

	Camera();
	~Camera();

	virtual void Update(float deltatime, GLFWwindow* window) = 0;
	void setPerspective(float fieldOfView, float aspectRatio, float near, float far);
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void setPosition(glm::vec3 position);

	glm::mat4 getWorldTransform();
	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::mat4 getProjectionView();

protected:

	void updateProjectionViewTransform();

	glm::mat4 worldTransform;
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;
	glm::mat4 view_x_projection;
};

