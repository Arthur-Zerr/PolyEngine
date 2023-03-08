//
// Created by Arthur Zerr on 12.02.23.
//

#ifndef POLYRPG_GAMEOBJECT_H
#define POLYRPG_GAMEOBJECT_H

#include <vector>
#include <glm/glm.hpp>

#include "ObjectComponents/BaseComponent.h"

namespace Engine
{
    class GameObject
    {
    private:
        std::vector<ObjectComponents::BaseComponent> components;

    public:
        char name[128] = "";

        float posX = 0.f;
        float posY = 0.f;
        float posZ = 0.f;

        float rotX = 0.f;
        float rotY = 0.f;
        float rotZ = 0.f;

        GameObject();

        bool isActive = true;

        void Init();

        void AddComponent(Engine::ObjectComponents::BaseComponent &component);

        void RemoveComponent(Engine::ObjectComponents::BaseComponent &component);

        glm::vec3 getVec3Position();

        glm::vec3 getVec3Rotation();
    };
}

#endif //POLYRPG_GAMEOBJECT_H
