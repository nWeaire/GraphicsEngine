#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Planet
{
public:
	Planet();
	~Planet();

	glm::mat4 localMatrix;
	glm::mat4 globalMatrix;

	Planet* plan = nullptr;
};

