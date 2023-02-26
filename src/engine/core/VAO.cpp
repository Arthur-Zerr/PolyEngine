//
// Created by Arthur Zerr on 04.02.23.
//

#include "VAO.h"

Engine::Core::VAO::VAO() {
    glGenVertexArrays(1, &Id); // Generate VAO before VBO !
    glBindVertexArray(Id); // Bind the VAO
}

void Engine::Core::VAO::LinkAttribute(Engine::Core::VBO &vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
    vbo.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout); // Enable the vertex Attribute
    vbo.UnBind();
}

void Engine::Core::VAO::Bind() {
    glBindVertexArray(Id); // Bind the VAO
}

void Engine::Core::VAO::UnBind() {
    glBindVertexArray(0); // unbind VAO
}

void Engine::Core::VAO::Dispose() {
    glDeleteVertexArrays(1, &Id);

}
