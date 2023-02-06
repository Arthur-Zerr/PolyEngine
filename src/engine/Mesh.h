//
// Created by Arthur Zerr on 06.02.23.
//

#ifndef POLYRPG_MESH_H
#define POLYRPG_MESH_H

#include <string>
#include <vector>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

#include "Camera.h"
#include "Vertex.h"


namespace Engine
{
    class Mesh
    {
    public:
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;

        VAO vao;

        Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures);

        void Draw(
                Shader &shader,
                Camera &camera,
                glm::mat4 matrix = glm::mat4(1.0f),
                glm::vec3 translation = glm::vec3(0.f, 0.f, 0.f),
                glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
                glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f)
        );

    };
}


#endif //POLYRPG_MESH_H
