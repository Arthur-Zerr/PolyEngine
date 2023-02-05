#include <iostream>

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "engine/Shader.h"
#include "engine/VAO.h"
#include "engine/VBO.h"
#include "engine/EBO.h"
#include "engine/Texture.h"
#include "engine/Camera.h"

#define WIDTH 1280
#define HEIGHT 720

// Vertices coordinates
// Vertices coordinates
GLfloat vertices[] =
        { //     COORDINATES     /        COLORS      /   TexCoord  //
                -0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
                -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
                0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
                0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
                0.0f, 0.8f, 0.0f, 0.92f, 0.86f, 0.76f, 2.5f, 5.0f
        };

// Indices for vertices order
GLuint indices[] =
        {
                0, 1, 2,
                0, 2, 3,
                0, 1, 4,
                1, 2, 4,
                2, 3, 4,
                3, 0, 4
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

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

    // Texture
    Engine::Texture groundTexture("textures/ground.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    groundTexture.textUnit(shaderProgram, "tex0", 0);

    glEnable(GL_DEPTH_TEST);

    Engine::Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    while (!glfwWindowShouldClose(window)) {
        // Update Stuff
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Render Stuff
        glViewport(0, 0, WIDTH, HEIGHT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.Activate();

        camera.Inputs(window);
        camera.Matrix(45.f, 0.1f, 100.f, shaderProgram, "camMatrix");

        groundTexture.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

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