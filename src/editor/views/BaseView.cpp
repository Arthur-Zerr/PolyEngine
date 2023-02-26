//
// Created by Arthur Zerr on 24.02.23.
//

#include "BaseView.h"

void PolyEngine::Editor::Views::BaseView::Init()
{

}

void PolyEngine::Editor::Views::BaseView::Render()
{
    ImGui::Begin("BaseView");
    ImGui::Text("Needs to be overridden!");
    ImGui::End();
}

void PolyEngine::Editor::Views::BaseView::Dispose()
{

}
