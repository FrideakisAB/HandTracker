#include "Mesh.h"

#include <vector>

void Mesh::Draw()
{
    if (VAO)
    {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indSize, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}

void Mesh::CreateCube()
{
	float s = 1.0f;
	std::vector<Vertex> vert = { //Front
								 {glm::vec3(-s, s, s),glm::vec3(0.0f, 0.0f, 1.0f),glm::vec2(0.0f, 1.0f)},
								 {glm::vec3(s, s, s),glm::vec3(0.0f, 0.0f, 1.0f),glm::vec2(1.0f, 1.0f)},
								 {glm::vec3(s,-s, s),glm::vec3(0.0f, 0.0f, 1.0f),glm::vec2(1.0f, 0.0f)},
								 {glm::vec3(-s,-s, s),glm::vec3(0.0f, 0.0f, 1.0f),glm::vec2(0.0f, 0.0f)},
								 //Back
								 {glm::vec3(s, s,-s),glm::vec3(0.0f, 0.0f, -1.0f),glm::vec2(0.0f, 1.0f)},
								 {glm::vec3(-s, s,-s),glm::vec3(0.0f, 0.0f, -1.0f),glm::vec2(1.0f, 1.0f)},
								 {glm::vec3(-s,-s,-s),glm::vec3(0.0f, 0.0f, -1.0f),glm::vec2(1.0f, 0.0f)},
								 {glm::vec3(s,-s,-s),glm::vec3(0.0f, 0.0f, -1.0f),glm::vec2(0.0f, 0.0f)},
								 //Top
								 {glm::vec3(-s, s,-s),glm::vec3(0.0f, 1.0f, 0.0f),glm::vec2(0.0f, 1.0f)},
								 {glm::vec3(s, s,-s),glm::vec3(0.0f, 1.0f, 0.0f),glm::vec2(1.0f, 1.0f)},
								 {glm::vec3(s, s, s),glm::vec3(0.0f, 1.0f, 0.0f),glm::vec2(1.0f, 0.0f)},
								 {glm::vec3(-s, s, s),glm::vec3(0.0f, 1.0f, 0.0f),glm::vec2(0.0f, 0.0f)},
								 //Bottom
								 {glm::vec3(s,-s,-s),glm::vec3(0.0f, -1.0f, 0.0f),glm::vec2(0.0f, 1.0f)},
								 {glm::vec3(-s,-s,-s),glm::vec3(0.0f, -1.0f, 0.0f),glm::vec2(1.0f, 1.0f)},
								 {glm::vec3(-s,-s, s),glm::vec3(0.0f, -1.0f, 0.0f),glm::vec2(1.0f, 0.0f)},
								 {glm::vec3(s,-s, s),glm::vec3(0.0f, -1.0f, 0.0f),glm::vec2(0.0f, 0.0f)},
								 //Left
								 {glm::vec3(-s, s,-s),glm::vec3(-1.0f, 0.0f, 0.0f),glm::vec2(0.0f, 1.0f)},
								 {glm::vec3(-s, s, s),glm::vec3(-1.0f, 0.0f, 0.0f),glm::vec2(1.0f, 1.0f)},
								 {glm::vec3(-s,-s, s),glm::vec3(-1.0f, 0.0f, 0.0f),glm::vec2(1.0f, 0.0f)},
								 {glm::vec3(-s,-s,-s),glm::vec3(-1.0f, 0.0f, 0.0f),glm::vec2(0.0f, 0.0f)},
								 //Right
								 {glm::vec3(s, s, s),glm::vec3(1.0f, 0.0f, 0.0f),glm::vec2(0.0f, 1.0f)},
								 {glm::vec3(s, s,-s),glm::vec3(1.0f, 0.0f, 0.0f),glm::vec2(1.0f, 1.0f)},
								 {glm::vec3(s,-s,-s),glm::vec3(1.0f, 0.0f, 0.0f),glm::vec2(1.0f, 0.0f)},
								 {glm::vec3(s,-s, s),glm::vec3(1.0f, 0.0f, 0.0f),glm::vec2(0.0f, 0.0f)}
	};

	std::vector<unsigned int> ind = { 0, 3, 1, 1, 3, 2,   // Front 
								 4, 7, 5, 5, 7, 6,   // Back 
								 8,11, 9, 9,11,10,   // Top 
								 12,15,13, 13,15,14, // Bottom 
								 16,19,17, 17,19,18, // Left 
								 20,23,21, 21,23,22  // Right 
	};

	indSize = ind.size();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(Vertex), &vert[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize * sizeof(unsigned int), &ind[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}