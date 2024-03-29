//
// Created by Arthur Zerr on 05.02.23.
//

#ifndef POLYRPG_CAMERA_H
#define POLYRPG_CAMERA_H

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "Shader.h"

namespace Engine {
    class Camera {
    public:
        glm::vec3 Position;
        glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::mat4 cameraMatrix = glm::mat4(1.0f);

        int width;
        int height;

        float speed = 0.001f;
        float sensitivity = 25.0f;

        Camera(int width, int height, glm::vec3 position);

        void UpdateWindowSize(int width, int height);
        void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);

        void Matrix(Shader &shader, const char *uniform);


        void Inputs(GLFWwindow *window);

    };
}


#endif //POLYRPG_CAMERA_H
