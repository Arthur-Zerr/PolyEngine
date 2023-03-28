#include <iostream>

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "engine/Shader.h"
#include "engine/Camera.h"

#include "engine/Model.h"
#include "engine/ObjModel.h"

#include "editor/EditorView.h"

#define WIDTH  1920
#define HEIGHT 1080

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

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
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GL_TRUE);

    // Create a window and its OpenGL context
    window = glfwCreateWindow(WIDTH, HEIGHT, "Poly Editor", NULL, NULL);
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

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    PolyEngine::Editor::EditorView editorView{window};
    editorView.Init();

    // Setup Platform/Renderer backends

//    Engine::Shader shaderProgram("shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
//    Engine::Shader treeShader("shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
//
//    glm::vec4 lightColor = glm::vec4(1.f, 1.f, 1.f, 1.f);
//    glm::vec3 lightPosition = glm::vec3(0.5f, 10.5f, 0.5f);
//    glm::mat4 lightModel = glm::mat4(1.0f);
//    lightModel = glm::translate(lightModel, lightPosition);
//
//    shaderProgram.Activate();
//    glUniform4f(glGetUniformLocation(shaderProgram.Id, "lightColor"), lightColor.x, lightColor.y, lightColor.z,
//                lightColor.w);
//    glUniform3f(glGetUniformLocation(shaderProgram.Id, "lightPosition"), lightPosition.x, lightPosition.y,
//                lightPosition.z);

    glEnable(GL_DEPTH_TEST);

//    treeShader.Activate();
//    glUniform4f(glGetUniformLocation(treeShader.Id, "lightColor"), lightColor.x, lightColor.y, lightColor.z,
//                lightColor.w);
//    glUniform3f(glGetUniformLocation(treeShader.Id, "lightPosition"), lightPosition.x, lightPosition.y,
//                lightPosition.z);
//    Engine::Models::ObjModel treeObjModel("objects/tree.obj");
//    treeObjModel.Load();

    Engine::Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.f, 0.f, 0.f, 0.f);

//        camera.UpdateWindowSize(width, height);

        // Render Stuff

//        camera.Inputs(window);
//        camera.UpdateMatrix(75.f, 0.01f, 500.f);

//        treeModel.Draw(shaderProgram, camera);
//        treeObjModel.Draw(treeShader, camera);

        editorView.Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    editorView.Dispose();
//    shaderProgram.Dispose();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

