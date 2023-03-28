//
// Created by Arthur Zerr on 12.02.23.
//

#ifndef POLYRPG_GAMEOBJECTPROPERTIESVIEW_H
#define POLYRPG_GAMEOBJECTPROPERTIESVIEW_H

#include "../../engine/GameObject.h"
#include "../../engine/Scene.h"
#include "BaseView.h"

namespace PolyEngine::Editor::Views
{
    class GameObjectPropertiesView : BaseView
    {
    private:
        /**
         * Renders the Position / Rotation inputs
         */
        void RenderTransform();

    public:
        std::string viewName;

        Engine::Scene *currentScene;
        Engine::GameObject *selectedGameObject;

        GameObjectPropertiesView(Engine::Scene *currentScene, Engine::GameObject *selectedGameObject);

        void Render();

        void Update();

        void Dispose();
    };
}

#endif //POLYRPG_GAMEOBJECTPROPERTIESVIEW_H
