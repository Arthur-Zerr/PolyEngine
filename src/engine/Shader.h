//
// Created by Arthur Zerr on 04.02.23.
//

#ifndef POLY_SHADER_H
#define POLY_SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

namespace Engine {

    std::string getFileContent(const char *filename);

    class Shader {

    public:
        GLuint Id;

        Shader(const char *vertexFile, const char *fragmentFile);

        void Activate();

        void Dispose();

    private:
        void compileErrors(unsigned int shader, const char *type);
    };
};

#endif //POLY_SHADER_H
