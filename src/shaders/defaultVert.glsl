#version 330 core

// Pos
layout (location = 0) in vec3 aPos;

// Color
layout (location = 1) in vec3 aColor;

// Texture position
layout (location = 2) in vec2 aTex;

layout (location = 3) in vec3 aNormal;


out vec3 color;
out vec2 texCoord;

out vec3 Normal;
out vec3 currentPosition;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
    currentPosition = vec3(model * vec4(aPos, 1.0f));
    Normal = aNormal;

    gl_Position = camMatrix * vec4(currentPosition, 1.0f);
    color = aColor;
    texCoord = aTex;
}