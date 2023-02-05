//
// Created by Arthur Zerr on 04.02.23.
//

#include "VBO.h"

Engine::VBO::VBO(GLfloat *vertices, GLsizeiptr size) {
    glGenBuffers(1, &Id);
    glBindBuffer(GL_ARRAY_BUFFER, Id); // Binds the VBO buffer to modify it
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); // Binds the vertices to the current bind buffer
}

void Engine::VBO::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, Id); // Binds the VBO buffer to modify it
}

void Engine::VBO::UnBind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO
}

void Engine::VBO::Dispose() {
    glDeleteBuffers(1, &Id);
}
