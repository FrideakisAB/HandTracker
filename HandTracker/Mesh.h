#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Mesh {
    unsigned int VAO = 0, VBO = 0, EBO = 0, indSize = 0;
    void Draw();
    void CreateCube();
};