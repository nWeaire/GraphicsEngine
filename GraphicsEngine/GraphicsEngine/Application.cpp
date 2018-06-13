#include "Application.h"



Application::Application()
{
}


Application::~Application()
{
}

int Application::Initialize(const glm::ivec2 & a_resolution, const char * a_name)
{
	cam = new FlyCamera();
	m_startTime = m_clock.now();
	m_currentTime = m_clock.now();
	m_previousTime = m_clock.now();

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
	screens = glfwGetMonitors(&count);

	glfwSetCursorPos(window, 720, 450);

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

	glClearColor(0.25f, 0.25f, 0.25f, 1);

	glEnable(GL_DEPTH_TEST);

	//AIE Gizmos
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	cam->setLookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	//view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	cam->setPerspective(0.25f, 16 / 9.f, 0.1f, 1000.f);
	//projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

	m_texturedShader.loadShader(aie::eShaderStage::VERTEX,
		"../shaders/textured.vert");
	m_texturedShader.loadShader(aie::eShaderStage::FRAGMENT,
		"../shaders/textured.frag");
	if (m_texturedShader.link() == false) {
		printf("Shader Error: %s\n", m_shader.getLastError());
		return false;
	}

	m_normalMapShader.loadShader(aie::eShaderStage::VERTEX,
		"../shaders/normalmap.vert");
	m_normalMapShader.loadShader(aie::eShaderStage::FRAGMENT,
		"../shaders/normalmap.frag");
	if (m_normalMapShader.link() == false) {
		printf("Shader Error: %s\n", m_shader.getLastError());
		return false;
	}

	m_phongShader.loadShader(aie::eShaderStage::VERTEX,
		"../shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT,
		"../shaders/phong.frag");
	if (m_phongShader.link() == false) {
		printf("Shader Error: %s\n", m_phongShader.getLastError());
		return false;
	}

	m_light.diffuse = { 1, 1, 1 };
	m_light.specular = { 0, 1, 0 };
	m_ambientLight = { 0.25f, 0.25f, 0.25f };
	m_light.direction = { 0, 0 , 1 };

	m_light2.diffuse = { 1, 1, 1 };
	m_light2.specular = { 0, 1, 0 };
	m_light2.direction = { 0, 0 , -1 };

	m_light3.diffuse = { 1, 1, 1 };
	m_light3.specular = { 0, 1, 0 };
	m_light3.direction = { 0, -1 , 0 };

	m_light4.diffuse = { 1, 1, 1 };
	m_light4.specular = { 0, 1, 0 };
	m_light4.direction = { 0, -1 , 0 };

	if (m_rockMesh.load("../Rock_6/Rock_6.obj", true, true) == false)
	{
		printf("tree Mesh Error!\n");
		return false;
	}
	m_rockTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		10,0,0,1
	};

	if (m_spearMesh2.load("../soulspear/soulspear.obj", true, true) == false)
	{
		printf("Soulspear Mesh Error!\n");
		return false;
	}
	m_spearTransform2 = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};


	if (m_spearMesh.load("../soulspear/soulspear.obj", true, true) == false) 
	{
		printf("Soulspear Mesh Error!\n");
		return false;
	}
	m_spearTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,4,1
	};
	
	if (m_houseMesh.load("../old_house_obj/house_01.obj", true, true) == false)
	{
		printf("House Mesh Error!\n");
		return false;
	}

	m_houseTransform = {
		0.1f,0,0,0,
		0,0.1f,0,0,
		0,0,0.1f,0,
		0,0,-10,1
	};


	if (m_bunnyMesh.load("../stanford/Bunny.obj") == false)
	{
		printf("Bunny Mesh Error!\n");
		return false;
	}
	m_bunnyTransform = {
		0.1f,0,0,0,
		0,0.1f,0,0,
		0,0,0.1f,0,
		0,0,-10,1
	};

	if (m_dummyMesh.load("../dummy_obj/dummy_obj.obj") == false)
	{
		printf("Dummy Mesh Error!\n");
		return false;
	}
	m_dummyTransform = {
		0.1f,0,0,0,
		0,0.1f,0,0,
		0,0,0.1f,0,
		-10,0,0,1
	};

	if (m_cameraMesh.load("../Models/Camera/leica.obj", true, true) == false)
	{
		printf("Camera Mesh Error!\n");
		return false;
	}
	m_cameraTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		10,15,0,1
	};

	if (m_renderTarget.initialise(1, a_resolution.x, a_resolution.y) == false) {
		printf("Render Target Error!\n");
		return false;
}

	m_quadMesh.initialiseQuad();

	//Make the quad 10 units wide
	m_quadTransform = 
	{ 10, 0, 0, 0,
		0, 10, 0, 0,
		0, 0, 10, 0,
		0, 0, 0, 1 }; 

	aie::Texture texture2;
	unsigned char texelData[4] = { 0, 255, 255, 0 };
	texture2.create(2, 2, aie::Texture::RED, texelData);

	return true;
}

void Application::Run()
{
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		m_previousTime = m_currentTime;
		m_currentTime = m_clock.now();
		auto duration = m_currentTime - m_previousTime;
		deltatime = duration.count() * NANO_TO_SECONDS;

		cam->Update(deltatime, window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// our game logic and update code goes here!
		// so does our render code!
		
		// query time since application started
		float time = glfwGetTime();
		// rotate light
		//m_light.direction = glm::normalize(glm::vec3(glm::cos(time * 2), 0,
			//glm::sin(time * 2)));

		aie::Gizmos::addTransform(glm::mat4(1));
		glm::vec4 white(1);
		glm::vec4 black(0, 0, 0, 1);
		for (int i = 0; i < 21; ++i) {

			aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), i == 10 ? white : black);
			aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), i == 10 ? white : black);
		}

		Render();
		glfwPollEvents();
	}
}

void Application::Render()
{
	//aie::Gizmos::draw(cam->getProjectionView());
	//aie::Gizmos::clear();

	// update perspective in case window resized
	cam->setPerspective(0.25f, 16 / 9.f, 0.1f, 1000.f);
	// bind shader
	//shader.bind();
	m_normalMapShader.bind();

	//// bind transform
	auto pvm = cam->getProjectionView() * m_houseTransform;

	m_normalMapShader.bindUniform("ProjectionViewModel", pvm);
	// bind transforms for lighting
	m_normalMapShader.bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_houseTransform)));
	m_normalMapShader.bindUniform("cameraPosition", glm::vec3(glm::inverse(m_viewMatrix)[3]));
	m_normalMapShader.bindUniform("Ia", m_ambientLight);
	m_normalMapShader.bindUniform("Id", m_light.diffuse);
	m_normalMapShader.bindUniform("Is", m_light.specular);
	m_normalMapShader.bindUniform("lightDirection", m_light.direction);

	// draw house
	m_houseMesh.draw();

	pvm = cam->getProjectionView() * m_spearTransform;

	m_normalMapShader.bindUniform("ProjectionViewModel", pvm);
	// bind transforms for lighting
	m_normalMapShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_spearTransform)));
	m_normalMapShader.bindUniform("cameraPosition", glm::vec3(glm::inverse(m_viewMatrix)[3]));
	m_normalMapShader.bindUniform("Ia", m_ambientLight);
	m_normalMapShader.bindUniform("Id", m_light2.diffuse);
	m_normalMapShader.bindUniform("Is", m_light2.specular);
	m_normalMapShader.bindUniform("lightDirection", m_light2.direction);

	// draw spear
	m_spearMesh.draw();

	pvm = cam->getProjectionView() * m_rockTransform;
	m_normalMapShader.bindUniform("ProjectionViewModel", pvm);

	// bind transforms for lighting
	m_normalMapShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_rockTransform)));
	m_normalMapShader.bindUniform("cameraPosition", glm::vec3(glm::inverse(m_viewMatrix)[3]));
	m_normalMapShader.bindUniform("Ia", m_ambientLight);
	m_normalMapShader.bindUniform("Id", m_light3.diffuse);
	m_normalMapShader.bindUniform("Is", m_light3.specular);
	m_normalMapShader.bindUniform("lightDirection", m_light3.direction);

	// draw spear
	m_rockMesh.draw();

	pvm = cam->getProjectionView() * m_cameraTransform;
	m_normalMapShader.bindUniform("ProjectionViewModel", pvm);

	// bind transforms for lighting
	m_normalMapShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_cameraTransform)));
	m_normalMapShader.bindUniform("cameraPosition", glm::vec3(glm::inverse(m_viewMatrix)[3]));
	m_normalMapShader.bindUniform("Ia", m_ambientLight);
	m_normalMapShader.bindUniform("Id", m_light4.diffuse);
	m_normalMapShader.bindUniform("Is", m_light4.specular);
	m_normalMapShader.bindUniform("lightDirection", m_light4.direction);

	// draw spear
	m_cameraMesh.draw();

	pvm = cam->getProjectionView() * m_dummyTransform;
	m_normalMapShader.bindUniform("ProjectionViewModel", pvm);

	m_texturedShader.bind();

	pvm = cam->getProjectionView() * m_dummyTransform;
	m_texturedShader.bindUniform("ProjectionViewModel", pvm);

	// draw Dummy
	m_dummyMesh.draw();

	pvm = cam->getProjectionView() * m_spearTransform2;
	m_texturedShader.bindUniform("ProjectionViewModel", pvm);
	
	m_spearMesh2.draw();

	// draw 3D gizmos
	aie::Gizmos::draw(cam->getProjectionView());

	glfwSwapBuffers(window);
	// draw 2D gizmos using an orthogonal projection matrix
	aie::Gizmos::draw2D(1440, 900);
}

void Application::Terminate()
{
	//Delete Gizmos
	aie::Gizmos::destroy();

	delete cam;

	//Clean up window and GPU linkage
	glfwTerminate();
}




