//
// Created by Arthur Zerr on 19.02.23.
//

#ifndef POLYRPG_SCENE_H
#define POLYRPG_SCENE_H

#include <string>
#include <vector>

#include "GameObject.h"

namespace Engine
{
    /**
     * Contains all level Information and gameObjects
     */
    class Scene
    {
    public:
        std::string sceneName;
        std::vector<GameObject> gameObjects;
    };
}
#endif //POLYRPG_SCENE_H
