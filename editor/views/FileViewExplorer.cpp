//
// Created by Arthur Zerr on 23.02.23.
//

#include "FileViewExplorer.h"

PolyEngine::Editor::Views::FileViewExplorer::FileViewExplorer()
{
    this->viewName = "FileViewExplorer";
}

void PolyEngine::Editor::Views::FileViewExplorer::Init()
{
    BaseView::Init();
}

void PolyEngine::Editor::Views::FileViewExplorer::Render()
{
    ImGui::Begin(this->viewName.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);
    ImGui::Text("File View");
    ImGui::End();
}

void PolyEngine::Editor::Views::FileViewExplorer::Dispose()
{
    BaseView::Dispose();
}
