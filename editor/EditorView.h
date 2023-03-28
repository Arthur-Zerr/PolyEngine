//
// Created by Arthur Zerr on 20.02.23.
//

#ifndef POLYRPG_EDITORVIEW_H
#define POLYRPG_EDITORVIEW_H

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"

#include "../engine/GameObject.h"
#include "../engine/Scene.h"

#include "CustomImGuiStyle.h"

#include "views/SceneEditorView.h"
#include "views/SceneExplorerView.h"
#include "views/GameObjectPropertiesView.h"
#include "views/FileViewExplorer.h"

namespace PolyEngine::Editor
{
    class EditorView
    {
    private:
        bool firstRun = true;

        GLFWwindow *window;
        Engine::Scene currentScene;
        Engine::GameObject currentGameObject;

        Views::SceneEditorView sceneEditorView{};
        Views::SceneExplorerView sceneExplorerView{&currentScene, &currentGameObject};
        Views::GameObjectPropertiesView gameObjectPropertiesView{&currentScene, &currentGameObject};
        Views::FileViewExplorer fileViewExplorer{};

        void createDockSpace(ImGuiID viewId);
        void renderMenuBar();

    public:
        EditorView(GLFWwindow *window);

        void Init();

        void Render();

        void Dispose();
    };
}


#endif //POLYRPG_EDITORVIEW_H
