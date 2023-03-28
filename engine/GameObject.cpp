//
// Created by Arthur Zerr on 12.02.23.
//

#include "GameObject.h"

Engine::GameObject::GameObject()
{

}

void Engine::GameObject::Init()
{

}

void Engine::GameObject::AddComponent(Engine::ObjectComponents::BaseComponent &component)
{
//    this->components.push_back(component);
}


void Engine::GameObject::RemoveComponent(Engine::ObjectComponents::BaseComponent &component)
{

}

glm::vec3 Engine::GameObject::getVec3Position()
{
    return glm::vec3{this->posX, this->posY, this->posZ};
}

glm::vec3 Engine::GameObject::getVec3Rotation()
{
    return glm::vec3{this->rotX, this->rotY, this->rotZ};
}
