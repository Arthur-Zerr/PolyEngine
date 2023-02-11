//
// Created by Arthur Zerr on 11.02.23.
//

#include "DebugView.h"

void Engine::Views::DebugView::Init()
{
}

void Engine::Views::DebugView::Render()
{
    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

    ImGui::SameLine();

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

