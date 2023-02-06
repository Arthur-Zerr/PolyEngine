//
// Created by Arthur Zerr on 05.02.23.
//

#include "Texture.h"

Engine::Texture::Texture(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
    this->type = texType;

    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);

    unsigned char *bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    glGenTextures(1, &this->Id);
    glActiveTexture(GL_TEXTURE0 + slot);
    unit = slot;

    glBindTexture(type, this->Id);

    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(type, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType,
                 bytes); // GL_RGB for jpg  GL_RGBA for pngs
    glGenerateMipmap(type);

    stbi_image_free(bytes);
    glBindTexture(type, 0);
}

void Engine::Texture::textUnit(Engine::Shader &shader, const char *uniform, GLuint unit) {
    GLuint tex0Uniform = glGetUniformLocation(shader.Id, uniform);
    shader.Activate();
    glUniform1i(tex0Uniform, unit);
}

void Engine::Texture::Bind() {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(type, this->Id);
}

void Engine::Texture::UnBind() {
    glBindTexture(type, 0);
}

void Engine::Texture::Dispose() {
    glDeleteTextures(1, &this->Id);

}
