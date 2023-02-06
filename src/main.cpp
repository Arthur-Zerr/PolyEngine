#include <iostream>

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "engine/Shader.h"
#include "engine/VBO.h"
#include "engine/EBO.h"
#include "engine/Texture.h"
#include "engine/Camera.h"

#include "engine/Mesh.h"
#include "engine/Model.h"

#define WIDTH  800
#define HEIGHT 800

int main()
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    // Set OpenGL Version, OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Set the OpenGL profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    // Create a window and its OpenGL context
    window = glfwCreateWindow(WIDTH, HEIGHT, "Poly RPG", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // load GLAD
    int gladErr = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    if (!gladErr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        throw;
    }
    gladLoadGL();

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);


    Engine::Shader shaderProgram("shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");


    glm::vec4 lightColor = glm::vec4(1.f, 1.f, 1.f, 1.f);
    glm::vec3 lightPosition = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPosition);


    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.Id, "lightColor"), lightColor.x, lightColor.y, lightColor.z,
                lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.Id, "lightPosition"), lightPosition.x, lightPosition.y,
                lightPosition.z);

    glEnable(GL_DEPTH_TEST);

    Engine::Model treeModel("objects/map/scene.gltf");

    Engine::Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    while (!glfwWindowShouldClose(window))
    {
        // Update Stuff
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }

        // Render Stuff
        glViewport(0, 0, WIDTH, HEIGHT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Inputs(window);
        camera.UpdateMatrix(45.f, 0.1f, 500.f);

        treeModel.Draw(shaderProgram, camera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shaderProgram.Dispose();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}