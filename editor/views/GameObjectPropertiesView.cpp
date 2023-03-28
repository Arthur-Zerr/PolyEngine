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

#pragma region PUBLIC

void PolyEngine::Editor::Views::GameObjectPropertiesView::Update()
{

}

void PolyEngine::Editor::Views::GameObjectPropertiesView::Render()
{
    ImGui::Begin(this->viewName.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);

    ImGui::Checkbox("##IsActive", &this->selectedGameObject->isActive);
    ImGui::SameLine();
    ImGui::Text("Name:");
    ImGui::SameLine();
    ImGui::InputText("##ObjectName", this->selectedGameObject->name, IM_ARRAYSIZE(this->selectedGameObject->name));

    this->RenderTransform();

    ImGui::End();
}

void PolyEngine::Editor::Views::GameObjectPropertiesView::Dispose()
{

}

#pragma endregion PUBLIC

#pragma region PRIVATE

void PolyEngine::Editor::Views::GameObjectPropertiesView::RenderTransform()
{

    if (ImGui::CollapsingHeader("Position", ImGuiTreeNodeFlags_DefaultOpen))
    {
        {
            ImGui::Text("X:");
            ImGui::SameLine();
            ImGui::SetNextItemWidth((ImGui::GetWindowWidth() / 3) - 35);
            ImGui::DragFloat("##posX", &this->selectedGameObject->posX, 1.f);
        }
        ImGui::SameLine();
        {
            ImGui::Text("Y:");
            ImGui::SameLine();
            ImGui::SetNextItemWidth((ImGui::GetWindowWidth() / 3) - 35);
            ImGui::DragFloat("##posY", &this->selectedGameObject->posY, 1.f);
        }
        ImGui::SameLine();
        {
            ImGui::Text("Z:");
            ImGui::SameLine();
            ImGui::SetNextItemWidth((ImGui::GetWindowWidth() / 3) - 35);
            ImGui::DragFloat("##posZ", &this->selectedGameObject->posZ, 1.f);
        }
    }

    if (ImGui::CollapsingHeader("Rotation", ImGuiTreeNodeFlags_DefaultOpen))
    {
        {
            ImGui::Text("X:");
            ImGui::SameLine();
            ImGui::SetNextItemWidth((ImGui::GetWindowWidth() / 3) - 35);
            ImGui::DragFloat("##rotX", &this->selectedGameObject->rotX, 1.f);

        }
        ImGui::SameLine();
        {
            ImGui::Text("Y:");
            ImGui::SameLine();
            ImGui::SetNextItemWidth((ImGui::GetWindowWidth() / 3) - 35);
            ImGui::DragFloat("##rotY", &this->selectedGameObject->rotY, 1.f);

        }
        ImGui::SameLine();
        {
            ImGui::Text("Z:");
            ImGui::SameLine();
            ImGui::SetNextItemWidth((ImGui::GetWindowWidth() / 3) - 35);
            ImGui::DragFloat("##rotZ", &this->selectedGameObject->rotZ, 1.f);
        }
    }
}

#pragma endregion PRIVATE