//
// Created by Arthur Zerr on 04.02.23.
//

#include "VAO.h"

Engine::VAO::VAO() {
    glGenVertexArrays(1, &Id); // Generate VAO before VBO !
    glBindVertexArray(Id); // Bind the VAO
}

void Engine::VAO::LinkAttribute(Engine::VBO &vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
    vbo.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout); // Enable the vertex Attribute
    vbo.UnBind();
}

void Engine::VAO::Bind() {
    glBindVertexArray(Id); // Bind the VAO
}

void Engine::VAO::UnBind() {
    glBindVertexArray(0); // unbind VAO
}

void Engine::VAO::Dispose() {
    glDeleteVertexArrays(1, &Id);

}
