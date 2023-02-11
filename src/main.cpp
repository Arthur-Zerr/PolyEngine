#include <iostream>

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "engine/Shader.h"
#include "engine/Camera.h"

#include "engine/Model.h"
#include "engine/ObjModel.h"

#include "engine/views/DebugView.h"

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

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");


    Engine::Shader shaderProgram("shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
    Engine::Shader treeShader("shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");

    glm::vec4 lightColor = glm::vec4(1.f, 1.f, 1.f, 1.f);
    glm::vec3 lightPosition = glm::vec3(0.5f, 10.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPosition);

    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.Id, "lightColor"), lightColor.x, lightColor.y, lightColor.z,
                lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.Id, "lightPosition"), lightPosition.x, lightPosition.y,
                lightPosition.z);

    glEnable(GL_DEPTH_TEST);

    treeShader.Activate();
    glUniform4f(glGetUniformLocation(treeShader.Id, "lightColor"), lightColor.x, lightColor.y, lightColor.z,
                lightColor.w);
    glUniform3f(glGetUniformLocation(treeShader.Id, "lightPosition"), lightPosition.x, lightPosition.y,
                lightPosition.z);

    glEnable(GL_DEPTH_TEST);

    Engine::Views::DebugView debugView;

    Engine::Model treeModel("objects/tree.gltf");
    Engine::Models::ObjModel treeObjModel("objects/tree.obj");
    treeObjModel.Load();

    Engine::Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        camera.UpdateWindowSize(width, height);

        // Update Stuff
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }

        // ImGUI stuff
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        debugView.Render();

        ImGui::Render();
        // Render Stuff
        glViewport(0, 0, width, height);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Inputs(window);
        camera.UpdateMatrix(75.f, 0.01f, 500.f);

        treeModel.Draw(shaderProgram, camera);
        treeObjModel.Draw(treeShader, camera);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    shaderProgram.Dispose();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

