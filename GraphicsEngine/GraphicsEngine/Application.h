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

	//-----------------------------------------------------
	// Function called on startup,
	// Initializes resolution and window size
	// Loads shaders and objects, setups up camera and transforms
	// Parameters:
	//		a_resolution: Resolution for the window created
	//		a_name: Name of the window
	//-----------------------------------------------------
	int Initialize(const glm::ivec2& a_resolution = glm::ivec2(1440, 900), const char* a_name = "Window");

	//-----------------------------------------------------
	// Update function called every frame
	//-----------------------------------------------------
	void Run();

	//-----------------------------------------------------
	// Draw function called every frame
	//-----------------------------------------------------
	void Render();

	//-----------------------------------------------------
	// Function called when program is closed
	//-----------------------------------------------------
	void Terminate();

protected:
	float deltatime; // Float to hold the value of deltaTime

	GLFWwindow* window; // OpenGL window
	GLFWmonitor** screens; // Number of screens for OpenGL

	glm::mat4 view; // Matrix4 containing the view transform
	glm::mat4 projection; // Matrix4 containing the projection transform

	wsp::clock m_clock; // Contains data based on time
	wsp::time m_startTime; // Time when program starts
	wsp::time m_currentTime; // Current time of program
	wsp::time m_previousTime; // Previous current time of program

	Camera* m_cam; // Reference to camera class
	
	glm::mat4			m_viewMatrix; // Matrix4 containing the view transform 
	glm::mat4			m_projectionMatrix; // Matrix4 containing the projection transform

	aie::ShaderProgram	m_shader; // Simple shader reference
	aie::ShaderProgram  m_normalMapShader; // Normal shader reference
	aie::ShaderProgram	m_texturedShader; // Textured shader reference
	aie::ShaderProgram	m_phongShader; // Phong shader reference
	aie::ShaderProgram	m_particleShader; // Particle shader reference

	Mesh				m_quadMesh; // Reference to mesh
	glm::mat4			m_quadTransform; // Tranformation matrix of quad

	Mesh				m_fullscreenQuad; // Fullscreen quad for post effects

	aie::OBJMesh		m_bunnyMesh; // Reference to bunny object
	glm::mat4			m_bunnyTransform; // Transformation matrix for bunny

	aie::OBJMesh		m_spearMesh; // Reference to spear object
	glm::mat4			m_spearTransform; // Transformation matrix for spear

	aie::OBJMesh		m_rifleMesh; // Reference to rifle object
	glm::mat4			m_rifleTransform; // Transformation matrix for rifle

	aie::OBJMesh		m_rockMesh; // Reference to rock object
	glm::mat4			m_rockTransform; // Transformation for rock

	aie::OBJMesh		m_spearMesh2; // Reference to spear object
	glm::mat4			m_spearTransform2; // Transformation matrix for spear2

	aie::OBJMesh		m_dummyMesh; // Reference to dummy object
	glm::mat4			m_dummyTransform; // Transformation matrix for dummy

	aie::OBJMesh		m_cameraMesh; // Reference to camera object
	glm::mat4			m_cameraTransform; // Transformation matrix for camera

	aie::Texture		m_gridTexture; // Grid texture

	ParticleEmitter		m_emitter; // Reference to particle emitter
	glm::mat4			m_particleTransform; // Tranformation matrix for particle

	struct Light // Light struct containing direction, diffuse and specular
	{
		glm::vec3 direction; // Direction the light faces
		glm::vec3 diffuse; // Diffuse for light
		glm::vec3 specular; // Specular for light
	};
	Light m_light; // Reference to light1
	Light m_light2; // Reference to light2
	Light m_light3; // Reference to light3
	Light m_light4; // Reference to light4
	glm::vec3 m_ambientLight; // Vector3 containing RBG of ambient light

};

