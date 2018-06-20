#pragma once
#include "glm.hpp"
#include "gl_core_4_5.h"
class Mesh
{
public:
	//-----------------------------------------------------
	// Default Constructor
	//-----------------------------------------------------
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {}

	//-----------------------------------------------------
	// Default Destructor
	//-----------------------------------------------------
	virtual ~Mesh();

	struct Vertex // Struct to hold vertex information
	{
		glm::vec4 position; // Position of vertex
		glm::vec4 normal; // Vertex's normal
		glm::vec2 texCoord; // Texture coordianate of vertex
	};

	//-----------------------------------------------------
	// Initialises mesh with a vertex count, vertices, Index count and indices
	// Parameter:
	//		int vertexCount: Number of vertices in the mesh
	//		Vertex* vertices: type of vertices in the mesh
	//		int indexCount: Number of indices in the mesh
	//		Vertex* indices: type of indices in the mesh
	//-----------------------------------------------------
	void initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount = 0, unsigned int* indices = nullptr);

	//-----------------------------------------------------
	// Initialises a quad shaped mesh
	//-----------------------------------------------------
	void initialiseQuad();

	//-----------------------------------------------------
	// Initialises a fullscreen quad mesh
	//-----------------------------------------------------
	void initialiseFullscreenQuad();

	//-----------------------------------------------------
	// Draw function to be called every frame
	//-----------------------------------------------------
	virtual void draw();

protected:
	unsigned int triCount; // Number of tris in mesh
	unsigned int vao, vbo, ibo;

};

