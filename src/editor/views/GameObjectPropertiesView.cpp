//
// Created by Arthur Zerr on 12.02.23.
//

#include "GameObjectPropertiesView.h"

PolyEngine::Editor::Views::GameObjectPropertiesView::GameObjectPropertiesView(Engine::Scene *currentScene,
                                                                              Engine::GameObject *selectedGameObject)
{
    this->viewName = "GameObjectPropertiesView";
    this->currentScene = currentScene;
    this->selectedGameObject = selectedGameObject;
}

void PolyEngine::Editor::Views::GameObjectPropertiesView::Update()
{

}

void PolyEngine::Editor::Views::GameObjectPropertiesView::Render()
{
    ImGui::Begin(this->viewName.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);

    ImGui::End();
}

void PolyEngine::Editor::Views::GameObjectPropertiesView::Dispose()
{

}

