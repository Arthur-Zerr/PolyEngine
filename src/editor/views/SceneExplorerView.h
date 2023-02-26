//
// Created by Arthur Zerr on 19.02.23.
//

#ifndef POLYRPG_SCENEEXPLORERVIEW_H
#define POLYRPG_SCENEEXPLORERVIEW_H

#include "imgui/imgui.h"

#include "../../engine/Scene.h"
#include "../../engine/GameObject.h"

#include "BaseView.h"

namespace PolyEngine::Editor::Views
{
    /**
     *  Contains all gameObjects from the currently loaded scene
     */
    class SceneExplorerView : BaseView
    {
    public:
        std::string viewName;

        Engine::Scene *currentScene;
        Engine::GameObject *selectedGameObject;

        SceneExplorerView(Engine::Scene *currentScene, Engine::GameObject *selectedGameObject);

        void Init() override;

        void Render() override;

        void Dispose() override;
    };
}


#endif //POLYRPG_SCENEEXPLORERVIEW_H
