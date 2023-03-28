//
// Created by Arthur Zerr on 05.02.23.
//

#include "Texture.h"

Engine::Texture::Texture(const char *image, const char *texType, GLenum slot)
{
    this->type = texType;

    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);

    unsigned char *bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    glGenTextures(1, &this->Id);
    glActiveTexture(GL_TEXTURE0 + slot);
    unit = slot;

    glBindTexture(GL_TEXTURE_2D, this->Id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (numColCh == 4)
        glTexImage2D
                (
                        GL_TEXTURE_2D,
                        0,
                        GL_RGBA,
                        widthImg,
                        heightImg,
                        0,
                        GL_RGBA,
                        GL_UNSIGNED_BYTE,
                        bytes
                );
    else if (numColCh == 3)
        glTexImage2D
                (
                        GL_TEXTURE_2D,
                        0,
                        GL_RGBA,
                        widthImg,
                        heightImg,
                        0,
                        GL_RGB,
                        GL_UNSIGNED_BYTE,
                        bytes
                );
    else if (numColCh == 1)
        glTexImage2D
                (
                        GL_TEXTURE_2D,
                        0,
                        GL_RGBA,
                        widthImg,
                        heightImg,
                        0,
                        GL_RED,
                        GL_UNSIGNED_BYTE,
                        bytes
                );
    else
    {
        throw std::invalid_argument("Automatic Texture type recognition failed");
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Engine::Texture::textUnit(Engine::Shader &shader, const char *uniform, GLuint unit)
{
    GLuint tex0Uniform = glGetUniformLocation(shader.Id, uniform);
    shader.Activate();
    glUniform1i(tex0Uniform, unit);
}

void Engine::Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, this->Id);
}

void Engine::Texture::UnBind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Engine::Texture::Dispose()
{
    glDeleteTextures(1, &this->Id);

}
