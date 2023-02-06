//
// Created by Arthur Zerr on 04.02.23.
//

#ifndef POLY_VBO_H
#define POLY_VBO_H

#include <glad/glad.h>
#include <vector>
#include "Vertex.h"

namespace Engine {
    class VBO {
    public:
        GLuint Id;

        VBO(std::vector<Vertex> &vertices);

        void Bind();

        void UnBind();

        void Dispose();
    };
}

#endif //POLY_VBO_H
