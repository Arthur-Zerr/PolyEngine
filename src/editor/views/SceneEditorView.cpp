//
// Created by Arthur Zerr on 12.02.23.
//

#include "SceneEditorView.h"

PolyEngine::Editor::Views::SceneEditorView::SceneEditorView()
{
    this->viewName = "SceneEditor";
}

void PolyEngine::Editor::Views::SceneEditorView::Init()
{
}

void PolyEngine::Editor::Views::SceneEditorView::Render()
{
    ImGui::Begin(this->viewName.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);
    ImGui::SetWindowSize(ImVec2((float) 1280, (float) 720));
    ImGui::Text("Render view of the current Scene");
    ImGui::Button("Test Button");
    ImGui::End();
}

void PolyEngine::Editor::Views::SceneEditorView::Dispose()
{

}