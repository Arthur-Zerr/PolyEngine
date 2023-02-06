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

#define WIDTH  800
#define HEIGHT 800

// Vertices coordinates
// Vertices coordinates
GLfloat vertices[] =
        {
                -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
        };

// Indices for vertices order
GLuint indices[] =
        {
                0, 1, 2,
                0, 2, 3
        };


GLfloat lightVertices[] =
        { //     COORDINATES     //
                -0.1f, -0.1f, 0.1f,
                -0.1f, -0.1f, -0.1f,
                0.1f, -0.1f, -0.1f,
                0.1f, -0.1f, 0.1f,
                -0.1f, 0.1f, 0.1f,
                -0.1f, 0.1f, -0.1f,
                0.1f, 0.1f, -0.1f,
                0.1f, 0.1f, 0.1f
        };

GLuint lightIndices[] =
        {
                0, 1, 2,
                0, 2, 3,
                0, 4, 7,
                0, 7, 3,
                3, 7, 6,
                3, 6, 2,
                2, 6, 5,
                2, 5, 1,
                1, 5, 4,
                1, 4, 0,
                4, 5, 6,
                4, 6, 7
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
    VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void *) 0);
    VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void *) (3 * sizeof(float)));
    VAO1.LinkAttribute(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void *) (6 * sizeof(float)));
    VAO1.LinkAttribute(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void *) (8 * sizeof(float)));

    // Unbind all to prevent accidentally modifying them
    VAO1.UnBind();
    VBO1.UnBind();
    EBO1.UnBind();

    Engine::Shader lightShader("shaders/lightVert.glsl", "shaders/lightFrag.glsl");
    Engine::VAO lightVAO;
    lightVAO.Bind();

    Engine::VBO lightVBO(lightVertices, sizeof(lightVertices));
    Engine::EBO lightEBO(lightIndices, sizeof(lightIndices));

    lightVAO.LinkAttribute(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *) 0);

    lightVAO.UnBind();
    lightEBO.UnBind();
    lightEBO.UnBind();

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    //TODO: test without equal sign
    glm::vec3 lightPosition = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPosition);

    glm::vec3 pyramidPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPosition);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.Id, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.Id, "lightColor"), lightColor.x, lightColor.y, lightColor.z,
                lightColor.w);


    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.Id, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(shaderProgram.Id, "lightColor"), lightColor.x, lightColor.y, lightColor.z,
                lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.Id, "lightPosition"), lightPosition.x, lightPosition.y,
                lightPosition.z);

    // Texture
    Engine::Texture groundTexture("textures/planks.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    groundTexture.textUnit(shaderProgram, "tex0", 0);


    Engine::Texture groundSpecularTexture("textures/planksSpec.jpg", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
    groundSpecularTexture.textUnit(shaderProgram, "tex1", 1);

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

        camera.Inputs(window);
        camera.UpdateMatrix(45.f, 0.1f, 100.f);

        shaderProgram.Activate();
        glUniform3f(glGetUniformLocation(shaderProgram.Id, "camPos"), camera.Position.x, camera.Position.y,
                    camera.Position.z);

        camera.Matrix(shaderProgram, "camMatrix");

        groundTexture.Bind();
        groundSpecularTexture.Bind();

        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        lightShader.Activate();
        camera.Matrix(lightShader, "camMatrix");
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

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