//
// Created by Arthur Zerr on 06.02.23.
//

#ifndef POLYRPG_VERTEX_H
#define POLYRPG_VERTEX_H

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace Engine {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
        glm::vec2 textUV;
    };
}

#endif //POLYRPG_VERTEX_H
