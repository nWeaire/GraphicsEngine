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
	Application App;

	App.Initialize();

	App.Run();
	
	App.Terminate();

	return 0;
}
