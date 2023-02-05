//
// Created by Arthur Zerr on 04.02.23.
//

#ifndef POLY_EBO_H
#define POLY_EBO_H

#include <glad/glad.h>

namespace Engine {

    class EBO {
    public:
        GLuint Id;

        EBO(GLuint *indices, GLsizeiptr size);

        void Bind();

        void UnBind();

        void Dispose();
    };
}


#endif //POLY_EBO_H
