//
// Created by Arthur Zerr on 04.02.23.
//

#include "Shader.h"

Engine::Shader::Shader(const char *vertexFile, const char *fragmentFile)
{
    std::string vertexCode = Engine::File::File::LoadFile(vertexFile);
    std::string fragmentCode = Engine::File::File::LoadFile(fragmentFile);

    // Convert the shader source strings into character arrays
    const char *vertexSource = vertexCode.c_str();
    const char *fragmentSource = fragmentCode.c_str();

    // Create Vertex Shader Object and get its reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertexShader);

    this->compileErrors(vertexShader, "VERTEX");


    // Create Fragment Shader Object and get its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(fragmentShader);

    this->compileErrors(fragmentShader, "FRAGMENT");

    // Create Shader Program Object and get its reference
    Id = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(Id, vertexShader);
    glAttachShader(Id, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(Id);
    this->compileErrors(Id, "PROGRAM");


    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

void Engine::Shader::Activate()
{
    glUseProgram(Id); // Use Shader program
}

void Engine::Shader::Dispose()
{
    glDeleteProgram(Id);
}

void Engine::Shader::compileErrors(unsigned int shader, const char *type)
{
    GLint hasCompiled;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_COMPILE_ERROR for:" << type << "\n" << std::endl;
        }
    } else
    {
        glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
        }
    }

}

