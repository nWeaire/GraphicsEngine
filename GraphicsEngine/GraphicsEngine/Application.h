#pragma once
#include <iostream>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "gl_core_4_5.h"
#include <glfw3.h>
#include "Gizmos.h"
#include "Camera.h"
#include "FlyCamera.h" 
#include "Mesh.h"
#include "Shader.h"
#include "OBJMesh.h"
#include "ParticleEmitter.h"
namespace wsp
{
	using clock = std::chrono::high_resolution_clock;
	using time = std::chrono::time_point<clock>;
}

/*TIME, CLOCK, AND DURATION Aliasing*/
using ullong = unsigned long long;
using nanoseconds = std::chrono::nanoseconds;
//Expected use: seconds = nanoseconds * NANO_TO_SECONDS
static const double NANO_TO_SECONDS = 0.000000001;
//Expected use: nanoseconds = seconds * NANO_TO_SECONDS
static const ullong NANO_IN_SECONDS = 1000000000ULL;

class Application
{
public:
	//-----------------------------------------------------
	// Default contructor
	//-----------------------------------------------------
	Application();

	//-----------------------------------------------------
	// Default destructor
	//-----------------------------------------------------
	~Application();

	int Initialize(const glm::ivec2& a_resolution = glm::ivec2(1440, 900), const char* a_name = "Window");
	void Run();
	void Render();
	void Terminate();

protected:
	float deltatime; // Float to hold the value of deltaTime

	GLFWwindow* window;
	GLFWmonitor** screens;

	glm::mat4 view;
	glm::mat4 projection;

	wsp::clock m_clock;
	wsp::time m_startTime;
	wsp::time m_currentTime;
	wsp::time m_previousTime;

	Camera* m_cam;
	
	glm::mat4			m_viewMatrix;
	glm::mat4			m_projectionMatrix;

	aie::ShaderProgram	m_shader;
	aie::ShaderProgram  m_normalMapShader;
	aie::ShaderProgram	m_texturedShader;
	aie::ShaderProgram	m_phongShader;
	aie::ShaderProgram	m_particleShader;

	Mesh				m_quadMesh;
	glm::mat4			m_quadTransform;

	Mesh				m_fullscreenQuad;

	aie::OBJMesh		m_bunnyMesh;
	glm::mat4			m_bunnyTransform;

	aie::OBJMesh		m_spearMesh;
	glm::mat4			m_spearTransform;

	aie::OBJMesh		m_rifleMesh;
	glm::mat4			m_rifleTransform;

	aie::OBJMesh		m_rockMesh;
	glm::mat4			m_rockTransform;

	aie::OBJMesh		m_spearMesh2;
	glm::mat4			m_spearTransform2;

	aie::OBJMesh		m_dummyMesh;
	glm::mat4			m_dummyTransform;

	aie::OBJMesh		m_cameraMesh;
	glm::mat4			m_cameraTransform;

	aie::Texture		m_gridTexture;

	ParticleEmitter		m_emitter;
	glm::mat4			m_particleTransform;

	struct Light 
	{
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
	Light m_light;
	Light m_light2;
	Light m_light3;
	Light m_light4;
	glm::vec3 m_ambientLight;

};

