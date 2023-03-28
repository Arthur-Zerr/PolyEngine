//
// Created by Arthur Zerr on 05.02.23.
//

#ifndef POLYRPG_TEXTURE_H
#define POLYRPG_TEXTURE_H

#include "glad/glad.h"
#include "stb/stb_image.h"

#include "Shader.h"

namespace Engine {
    class Texture {
    public:
        GLuint Id;
        const char *type;
        GLuint unit;

        Texture(const char *image, const char * texType, GLenum slot);

        void textUnit(Shader &shader, const char *uniform, GLuint unit);

        void Bind();

        void UnBind();

        void Dispose();

    };
}


#endif //POLYRPG_TEXTURE_H
