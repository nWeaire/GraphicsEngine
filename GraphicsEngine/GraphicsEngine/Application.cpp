#include "Application.h"

//-----------------------------------------------------
// Default contructor
//-----------------------------------------------------
Application::Application()
{
}

//-----------------------------------------------------
// Default destructor
//-----------------------------------------------------
Application::~Application()
{
}

//-----------------------------------------------------
// Function called on startup,
// Initializes resolution and window size
// Loads shaders and objects, setups up camera and transforms
// Parameters:
//		a_resolution: Resolution for the window created
//		a_name: Name of the window
//-----------------------------------------------------
int Application::Initialize(const glm::ivec2 & a_resolution, const char * a_name)
{
	m_cam = new FlyCamera();
	m_startTime = m_clock.now(); // Start time of program
	m_currentTime = m_clock.now(); // Current time of program
	m_previousTime = m_clock.now(); // Previous time of program

	// If we can hook into the GPU
	if (glfwInit() == false)
		return -1; // -1 is a failure code 

    //Make a window with openGL render Width, Height, Window name, Screen pointer
	window = glfwCreateWindow(a_resolution.x,a_resolution.y, a_name, nullptr, nullptr);

	//Check window worked
	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	int count = 0;
	screens = glfwGetMonitors(&count); // Gets number of monitors

	glfwSetCursorPos(window, 720, 450); // Sets cursor position in screen space

	//Bring to front
	glfwMakeContextCurrent(window);

	// before loading interface
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	//Open GL Version
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	glClearColor(0.25f, 0.25f, 0.25f, 1); // Sets background colour

	glEnable(GL_DEPTH_TEST);

	//AIE Gizmos
	aie::Gizmos::create(10000, 10000, 10000, 10000); // Creates gizmos class with a max of 10000 lines and tris

	m_cam->setLookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0)); // Sets cameras position, what to look at and from which rotation
	m_cam->setPerspective(0.25f, 16 / 9.f, 0.1f, 1000.f); // Sets perspective of camera

	//-----------------------------------------------------------------
	// Loads and error checks all shaders in scene
	//-----------------------------------------------------------------
	m_texturedShader.loadShader(aie::eShaderStage::VERTEX,	"../shaders/textured.vert"); // Loads Textured shader vert file
	m_texturedShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/textured.frag"); // Loads Textured shader frag file
	if (m_texturedShader.link() == false) // Links shader to program, Checks if failed
	{
		printf("Shader Error: %s\n", m_shader.getLastError()); // If failed print error to console
		return false; // End program
	}

	m_normalMapShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/normalmap.vert"); // Load Normal shader vert file
	m_normalMapShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/normalmap.frag"); // Load Normal shader frag file
	if (m_normalMapShader.link() == false) // Links shader to program, Checks if failed
	{
		printf("Shader Error: %s\n", m_shader.getLastError()); // If failed print error to console
		return false; // End program
	}

	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/phong.vert"); // Load Phong shader vert file
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/phong.frag"); // Load Phong shader frag file
	if (m_phongShader.link() == false) // Links shader to program, Checks if failed
	{
		printf("Shader Error: %s\n", m_phongShader.getLastError()); // If failed print error to console
		return false; // End program
	}

	m_particleShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/particle.vert"); // Load Particle shader vert file
	m_particleShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/particle.frag"); // Load Particle shader frag file
	if (m_particleShader.link() == false) // Links shader to program, Checks if failed
	{
		printf("Shader Error: %s\n", m_particleShader.getLastError()); // If failed print error to console
		return false; // End program
	}

	//-----------------------------------------------------------------
	// Sets values for all lighting in the scene
	//-----------------------------------------------------------------
	m_light.diffuse = { 1, 1, 1 }; // Sets diffuse values for light
	m_light.specular = { 0, 1, 0 }; // Sets specular values for light
	m_light.direction = { 0, 0 , 1 }; // Sets lights direction

	m_light2.diffuse = { 1, 1, 1 }; // Sets diffuse values for light
	m_light2.specular = { 0, 1, 0 }; // Sets specular values for light
	m_light2.direction = { 0, 0 , -1 }; // Sets lights direction

	m_light3.diffuse = { 1, 1, 1 }; // Sets diffuse values for light
	m_light3.specular = { 0, 1, 0 }; // Sets specular values for light
	m_light3.direction = { 0, -1 , 0 }; // Sets lights direction

	m_light4.diffuse = { 1, 1, 1 }; // Sets diffuse values for light
	m_light4.specular = { 0, 1, 0 }; // Sets specular values for light
	m_light4.direction = { 0, -1 , 0 }; // Sets lights direction

	m_ambientLight = { 0.25f, 0.25f, 0.25f }; // Sets ambient light for the scene


	//-----------------------------------------------------------------
	// Loads models and sets there transforms
	//-----------------------------------------------------------------
	if (m_rockMesh.load("../Rock_6/Rock_6.obj", true, true) == false) // Loads rock obj file and rock textures
	{
		printf("Rock Mesh Error!\n");  // If failed to load print error to console
		return false;
	}

	// Sets Rock Tranform with a new matrix4
	m_rockTransform = 
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		10,0,0,1
	};

	if (m_spearMesh2.load("../soulspear/soulspear.obj", true, true) == false) // Loads in Soulspear obj and textures
	{
		printf("Soulspear Mesh Error!\n"); // If failed to load print error to console
		return false;
	}

	// Sets SoulSpear Tranform with a new matrix4
	m_spearTransform2 = 
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	if (m_spearMesh.load("../soulspear/soulspear.obj", true, true) == false) // Loads in Soulspear obj and textures
	{
		printf("Soulspear Mesh Error!\n"); // If failed to load print error to console
		return false;
	}

	// Sets SoulSpear Tranform with a new matrix4
	m_spearTransform = 
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,4,1
	};
	
	if (m_rifleMesh.load("../Models/Rifle/Rifle.obj", true, true) == false) // Loads in Rifle obj and textures
	{
		printf("Rifle Mesh Error!\n"); // If failed to load print error to console
		return false;
	}

	// Sets Rifle Tranform with a new matrix4
	m_rifleTransform = 
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,-10,1
	};

	if (m_dummyMesh.load("../dummy_obj/dummy_obj.obj") == false) // Loads in Dummy obj and textures
	{
		printf("Dummy Mesh Error!\n"); // If failed to load print error to console
		return false;
	}

	// Sets Dummy Tranform with a new matrix4
	m_dummyTransform = 
	{
		0.1f,0,0,0,
		0,0.1f,0,0,
		0,0,0.1f,0,
		-10,0,0,1
	};

	if (m_cameraMesh.load("../Models/Camera/leica.obj", true, true) == false) // Loads in Camera obj and textures
	{
		printf("Camera Mesh Error!\n"); // If failed to load print error to console
		return false;
	}

	// Sets Camera Tranform with a new matrix4
	m_cameraTransform =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		10,15,0,1
	};

	// Sets Particle Tranform with a new matrix4
	m_particleTransform = 
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,10,0,1 
	};

	// Inializes particle emitter with variables for particle amount, emit rate, life time, colour, size and position
	m_emitter.initalise(1000, 500, 0.1f, 1.0f, 1, 5, 1, 0.1f, glm::vec4(1, 0, 0, 1), glm::vec4(1, 1, 0, 1));

	return true;
}

//-----------------------------------------------------
// Update function called every frame
// Builds grid with x,y and z axis
// Updates camera
// Updates deltaTime
// Updates emitter
//-----------------------------------------------------
void Application::Run()
{
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		m_previousTime = m_currentTime; // Updates previous time
		m_currentTime = m_clock.now(); // Sets current time to now
		auto duration = m_currentTime - m_previousTime; // Calculates duration
		deltatime = duration.count() * NANO_TO_SECONDS; // Calculates deltaTime

		m_cam->Update(deltatime, window); // Update camera
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear openGl colour and depth buffer

		aie::Gizmos::addTransform(glm::mat4(1)); 
		glm::vec4 white(1);
		glm::vec4 black(0, 0, 0, 1);
		for (int i = 0; i < 21; ++i) // Builds grid
		{

			aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), i == 10 ? white : black);
			aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), i == 10 ? white : black);
		}
		m_emitter.update(deltatime, m_cam->getWorldTransform()); // Updates particle emitter
		Render(); // Renders scene
		glfwPollEvents();
	}
}

//-----------------------------------------------------
// Draw function called every frame
// Renders all objects in scene
// Binds shaders to the scene
//-----------------------------------------------------
void Application::Render()
{
	aie::Gizmos::draw(m_cam->getProjectionView()); // Draws gizmos with cameras view
	aie::Gizmos::clear(); // Clears screen

	// update perspective in case window resized
	m_cam->setPerspective(0.25f, 16 / 9.f, 0.1f, 1000.f);

	//-----------------------------------------------------------------
	// Binds Shaders, Shader Uniforms, Sets camera view on the objects transform and draws objects
	//-----------------------------------------------------------------

	m_normalMapShader.bind(); // Bind the normal shader to the scene

	// bind transform
	auto pvm = m_cam->getProjectionView() * m_rifleTransform; // Sets project view model to cameras view * the objects transform
	m_normalMapShader.bindUniform("ProjectionViewModel", pvm); // Binds projection view model to the shader

	// bind transforms for lighting
	m_normalMapShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_rifleTransform))); // Bind the normal matrix to the shader
	m_normalMapShader.bindUniform("cameraPosition", glm::vec3(glm::inverse(m_viewMatrix)[3])); // Binds the camera position to the shader
	m_normalMapShader.bindUniform("Ia", m_ambientLight); // Binds the ambient light to the shader
	m_normalMapShader.bindUniform("Id", m_light.diffuse); // Binds the lights diffuse value to the shader
	m_normalMapShader.bindUniform("Is", m_light.specular); // Binds the lights Specular value to the shader
	m_normalMapShader.bindUniform("lightDirection", m_light.direction); // Binds the lights direction to the shader

    // Draws Multi textured lit rifle
	m_rifleMesh.draw();

	pvm = m_cam->getProjectionView() * m_spearTransform; // Sets project view model to cameras view * the objects transform
	m_normalMapShader.bindUniform("ProjectionViewModel", pvm); // Binds projection view model to the shader

	// bind transforms for lighting
	m_normalMapShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_spearTransform))); // Bind the normal matrix to the shader
	m_normalMapShader.bindUniform("cameraPosition", glm::vec3(glm::inverse(m_viewMatrix)[3])); // Binds the camera position to the shader
	m_normalMapShader.bindUniform("Ia", m_ambientLight); // Binds the ambient light to the shader
	m_normalMapShader.bindUniform("Id", m_light2.diffuse); // Binds the lights diffuse value to the shader
	m_normalMapShader.bindUniform("Is", m_light2.specular); // Binds the lights Specular value to the shader
	m_normalMapShader.bindUniform("lightDirection", m_light2.direction); // Binds the lights direction to the shader

	// Draws Multi textured lit spear
	m_spearMesh.draw();

	pvm = m_cam->getProjectionView() * m_rockTransform; // Sets project view model to cameras view * the objects transform
	m_normalMapShader.bindUniform("ProjectionViewModel", pvm); // Binds projection view model to the shader

	// bind transforms for lighting
	m_normalMapShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_rockTransform))); // Bind the normal matrix to the shader
	m_normalMapShader.bindUniform("cameraPosition", glm::vec3(glm::inverse(m_viewMatrix)[3])); // Binds the camera position to the shader
	m_normalMapShader.bindUniform("Ia", m_ambientLight); // Binds the ambient light to the shader
	m_normalMapShader.bindUniform("Id", m_light3.diffuse); // Binds the lights diffuse value to the shader
	m_normalMapShader.bindUniform("Is", m_light3.specular); // Binds the lights Specular value to the shader
	m_normalMapShader.bindUniform("lightDirection", m_light3.direction); // Binds the lights direction to the shader

	// Draws Multi textured lit spear
	m_rockMesh.draw();

	pvm = m_cam->getProjectionView() * m_cameraTransform; // Sets project view model to cameras view * the objects transform
	m_normalMapShader.bindUniform("ProjectionViewModel", pvm); // Binds projection view model to the shader

	// bind transforms for lighting
	m_normalMapShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_cameraTransform))); // Bind the normal matrix to the shader
	m_normalMapShader.bindUniform("cameraPosition", glm::vec3(glm::inverse(m_viewMatrix)[3])); // Binds the camera position to the shader
	m_normalMapShader.bindUniform("Ia", m_ambientLight); // Binds the ambient light to the shader
	m_normalMapShader.bindUniform("Id", m_light4.diffuse); // Binds the lights diffuse value to the shader
	m_normalMapShader.bindUniform("Is", m_light4.specular); // Binds the lights Specular value to the shader
	m_normalMapShader.bindUniform("lightDirection", m_light4.direction); // Binds the lights direction to the shader

	// Draws Multi textured lit camera
	m_cameraMesh.draw();

	pvm = m_cam->getProjectionView() * m_dummyTransform; // Sets project view model to cameras view * the objects transform
	m_normalMapShader.bindUniform("ProjectionViewModel", pvm); // Binds projection view model to the shader

	// Binds Textured shader
	m_texturedShader.bind();

	pvm = m_cam->getProjectionView() * m_dummyTransform; // Sets project view model to cameras view * the objects transform
	m_texturedShader.bindUniform("ProjectionViewModel", pvm); // Binds projection view model to the shader

	// draw Dummy
	m_dummyMesh.draw();

	pvm = m_cam->getProjectionView() * m_spearTransform2; // Sets project view model to cameras view * the objects transform
	m_texturedShader.bindUniform("ProjectionViewModel", pvm); // Binds projection view model to the shader
	
	// Draws Textured spear
	m_spearMesh2.draw();

	// bind particle shader
	m_particleShader.bind();

	// bind particle transform
	pvm = m_cam->getProjectionView() * m_particleTransform; // Sets project view model to cameras view * the objects transform
	m_particleShader.bindUniform("ProjectionViewModel", pvm); // Binds projection view model to the shader
	m_emitter.draw(); // draws particles into scene

	// draw 3D gizmos
	aie::Gizmos::draw(m_cam->getProjectionView()); 

	glfwSwapBuffers(window);
	// draw 2D gizmos using an orthogonal projection matrix
	aie::Gizmos::draw2D(1440, 900);
}

//-----------------------------------------------------
// Function called when program is closed
//-----------------------------------------------------
void Application::Terminate()
{
	//Delete Gizmos
	aie::Gizmos::destroy();

	// Deletes camera
	delete m_cam;

	//Clean up window and GPU linkage
	glfwTerminate();
}




