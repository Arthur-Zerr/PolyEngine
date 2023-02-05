//
// Created by Arthur Zerr on 04.02.23.
//

#ifndef POLY_VAO_H
#define POLY_VAO_H

#include <glad/glad.h>
#include "VBO.h"

namespace Engine {
    class VAO {
    public:
        GLuint Id;

        VAO();

        void LinkAttribute(VBO &vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

        void Bind();

        void UnBind();

        void Dispose();
    };

}


#endif //POLY_VAO_H
