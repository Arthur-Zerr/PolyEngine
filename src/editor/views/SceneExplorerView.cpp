//
// Created by Arthur Zerr on 19.02.23.
//

#include "SceneExplorerView.h"

PolyEngine::Editor::Views::SceneExplorerView::SceneExplorerView(Engine::Scene *currentScene,
                                                                Engine::GameObject *selectedGameObject)
{
    this->viewName = "SceneExplorerView";
    this->currentScene = currentScene;
    this->selectedGameObject = selectedGameObject;
}

void PolyEngine::Editor::Views::SceneExplorerView::Init()
{

}

void PolyEngine::Editor::Views::SceneExplorerView::Render()
{
    ImGui::Begin(this->viewName.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);
    ImGui::SetWindowSize(ImVec2((float) 1280, (float) 720));
    ImGui::Text("Contains all Gameobjects currently on the Scene as a list");
    ImGui::Button("Test Button");
    ImGui::End();
}

void PolyEngine::Editor::Views::SceneExplorerView::Dispose()
{

}

