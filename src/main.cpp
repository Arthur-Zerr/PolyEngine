#include <iostream>

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <cmath>

#include "engine/Shader.h"
#include "engine/VAO.h"
#include "engine/VBO.h"
#include "engine/EBO.h"
#include "engine/Texture.h"


#define WIDTH 800
#define HEIGHT 800

// Vertices coordinates
GLfloat vertices[] =
        { //     COORDINATES                        /        COLORS                 /   TexCoord             //
                -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Lower left corner
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Upper left corner
                0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Upper right corner
                0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f  // Lower right corner
        };

// Indices for vertices order
GLuint indices[] =
        {
                0, 2, 1, // Upper triangle
                0, 3, 2 // Lower triangle
        };


int main() {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // Set OpenGL Version, OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Set the OpenGL profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    // Create a window and its OpenGL context
    window = glfwCreateWindow(WIDTH, HEIGHT, "Poly RPG", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // load GLAD
    int gladErr = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    if (!gladErr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        throw;
    }
    gladLoadGL();

    Engine::Shader shaderProgram("shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");

    // Generates Vertex Array Object and binds it
    Engine::VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    Engine::VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    Engine::EBO EBO1(indices, sizeof(indices));

    // Links VBO to VAO
    VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *) 0);
    VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    VAO1.LinkAttribute(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *) (6 * sizeof(float)));


    // Unbind all to prevent accidentally modifying them
    VAO1.UnBind();
    VBO1.UnBind();
    EBO1.UnBind();

    GLuint uniId = glGetUniformLocation(shaderProgram.Id, "scale");


    // Texture
    Engine::Texture groundTexture("textures/ground.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    groundTexture.textUnit(shaderProgram, "tex0", 0);

    while (!glfwWindowShouldClose(window)) {
        // Update Stuff
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Render Stuff
        glViewport(0, 0, WIDTH, HEIGHT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Activate();
        glUniform1f(uniId, 0.5f);

        groundTexture.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shaderProgram.Dispose();
    VAO1.Dispose();
    VBO1.Dispose();
    EBO1.Dispose();
    groundTexture.Dispose();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}