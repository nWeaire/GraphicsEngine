#include "Application.h"
#include <iostream>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../Dep/glCore/gl_core_4_5.h"
#include <glfw3.h>

#include "Gizmos.h"


int main()
{
	// Makes instance of application
	Application App;
	
	// Calls startup function for the application
	App.Initialize();

	// Calls the update function of the application
	App.Run();
	
	// Calls the terminate function for the application
	App.Terminate();

	// Returns 0 if all pasted
	return 0;
}
