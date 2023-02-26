//
// Created by Arthur Zerr on 12.02.23.
//

#ifndef POLYRPG_GAMEOBJECT_H
#define POLYRPG_GAMEOBJECT_H

#include <vector>

#include "ObjectComponents/BaseComponent.h"

namespace Engine
{
    class GameObject
    {
    private:
        std::vector<ObjectComponents::BaseComponent> components;

    public:
        GameObject();
        void Init();
        void AddComponent(Engine::ObjectComponents::BaseComponent &component);

    };
}

#endif //POLYRPG_GAMEOBJECT_H
