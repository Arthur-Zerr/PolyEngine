//
// Created by Arthur Zerr on 05.02.23.
//

#include "Camera.h"

Engine::Camera::Camera(int width, int height, glm::vec3 position)
{
    this->width = width;
    this->height = height;
    this->Position = position;
}

void
Engine::Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
{

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(FOVdeg), float(width / height), nearPlane, farPlane);

    this->cameraMatrix = projection * view;
}

void Engine::Camera::Inputs(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        this->Position += speed * Orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        this->Position -= speed * Orientation;

    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        this->Position += speed * -glm::normalize(glm::cross(Orientation, Up));

    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        this->Position += speed * glm::normalize(glm::cross(Orientation, Up));
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        this->Position += speed * Up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        this->Position += speed * -Up;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        this->speed = 0.04f;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        this->speed = 0.01;
    }

    double mouseX;
    double mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    float rotx = sensitivity * (float) (mouseY - (height / 2)) / height;
    float roty = sensitivity * (float) (mouseX - (width / 2)) / width;

    glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotx),
                                           glm::normalize(glm::cross(Orientation, Up)));

    if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
    {
//        Orientation = newOrientation;
    }

//    Orientation = glm::rotate(Orientation, glm::radians(-roty), Up);

//    glfwSetCursorPos(window, (width / 2), (height / 2));
}

void Engine::Camera::Matrix(Engine::Shader &shader, const char *uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.Id, uniform), 1, GL_FALSE, glm::value_ptr(this->cameraMatrix));
}

void Engine::Camera::UpdateWindowSize(int width, int height)
{
    this->width = width;
    this->height = height;
}
