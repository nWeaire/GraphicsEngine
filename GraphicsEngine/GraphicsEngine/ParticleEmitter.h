#pragma once
#include "gl_core_4_5.h"
#include <glm.hpp>
class ParticleEmitter
{
public:
	//-----------------------------------------------------
	// Default Constructor
	//-----------------------------------------------------
	ParticleEmitter();

	//-----------------------------------------------------
	// Default Destructor
	//-----------------------------------------------------
	virtual ~ParticleEmitter();

	//-----------------------------------------------------
	// Initalises particles with given parameters
	// parameters:
	//		int a_maxParticles:	Max particles that can spawn
	//		int a_emitRate: Rate the particles spawn
	//		float a_lifeTimeMin: Minimum time a particle lasts
	//		float a_lifetimeMax: Maximum time a particle can last
	//		float a_velocityMin: Minimum velocity a particle can move
	//		float a_velocityMax: Maximum valocity a particle can move
	//		float a_startSize: Starting size of particle
	//		float a_endSize: End size of particle
	//		Vector4 a_startColour: Starting colour of particle
	//		Vector4 a_endColour: End colour of particle
	//-----------------------------------------------------
	void initalise(unsigned int a_maxParticles, unsigned int a_emitRate, float a_lifetimeMin, float a_lifetimeMax, float a_velocityMin, float a_velocityMax, float a_startSize, float a_endSize, const glm::vec4& a_startColour, const glm::vec4& a_endColour);
	
	//-----------------------------------------------------
	// Emits particles in scene
	//-----------------------------------------------------
	void emit();

	//-----------------------------------------------------
	// Update function to call each frame
	// Parameters:
	//		float deltaTime: deltaTime value to use for updates
	//		float window: The instance of window
	//-----------------------------------------------------
	void update(float a_deltaTime, const glm::mat4 & a_cameraTransform);

	//-----------------------------------------------------
	// Draw function called every frame
	//-----------------------------------------------------
	void draw();

	struct Particle // Holds the particle information 
	{
		glm::vec3 position; // position of the particle
		glm::vec3 velocity; // Velocity of the particle
		glm::vec4 colour; // Colour of the particle
		float size; // Size of the particle
		float lifetime; // Lifetime of the particle
		float lifespan; // Lifespan of the particle
	};
	struct ParticleVertex // Particle vertex information 
	{
		glm::vec4 position; // Position of vertex
		glm::vec4 colour; // Colour of vertex
	};

protected:

	Particle* m_particles; // Pointer to particles
	unsigned int m_firstDead; // First particle to die
	unsigned int m_maxParticles; // Max number of particles from emitter
	unsigned int m_vao, m_vbo, m_ibo; 

	ParticleVertex* m_vertexData; // Particles vertex data


	glm::vec3 m_position; // Position of emitter
	float m_emitTimer; // timer to control emit rate
	float m_emitRate; // Rate to emit particles
	float m_lifespanMin; // Minimum life span of particle
	float m_lifespanMax; // Maximum life span of particle
	float m_velocityMin; // Minimum velocity of particle
	float m_velocityMax; // Maximum velocity of particle
	float m_startSize; // Start size of particle
	float m_endSize; // End size of particle
	glm::vec4 m_startColour; // Start colour of particle
	glm::vec4 m_endColour; // End colour of particle

};

