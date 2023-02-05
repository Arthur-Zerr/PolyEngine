//
// Created by Arthur Zerr on 04.02.23.
//

#include "EBO.h"

Engine::EBO::EBO(GLuint *indices, GLsizeiptr size) {
    glGenBuffers(1, &Id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id); // Bind the EBO as the current buffer to modify
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices,
                 GL_STATIC_DRAW); // Binds the indicies to the current bind buffer
}

void Engine::EBO::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id); // Bind the EBO as the current buffer to modify

}

void Engine::EBO::UnBind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind after VAO !
}

void Engine::EBO::Dispose() {
    glDeleteBuffers(1, &Id);
}
