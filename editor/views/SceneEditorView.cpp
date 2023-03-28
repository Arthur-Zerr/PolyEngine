//
// Created by Arthur Zerr on 12.02.23.
//

#include "SceneEditorView.h"

PolyEngine::Editor::Views::SceneEditorView::SceneEditorView()
{
    this->viewName = "SceneEditor";
    this->windowWidth = 1280;
    this->windowHeight = 720;
}

void PolyEngine::Editor::Views::SceneEditorView::Init()
{
    this->InitScene();
    this->InitSceneFramebuffer();
}

void PolyEngine::Editor::Views::SceneEditorView::Render()
{
    ImGui::Begin(this->viewName.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);
    this->windowWidth = ImGui::GetWindowViewport()->Size.x;
    this->windowHeight = ImGui::GetWindowViewport()->Size.y;

    this->RescaleSceneFramebuffer();
    this->RenderScene();

    ImGui::Image(
            (void *) (ImTextureID)this->sceneTexture,
            ImGui::GetContentRegionAvail(),
            ImVec2(0, 1),
            ImVec2(1, 0)
    );
    ImGui::End();
}

void PolyEngine::Editor::Views::SceneEditorView::Dispose()
{
    glDeleteFramebuffers(1, &this->sceneFramebuffer);
    glDeleteTextures(1, &this->sceneTexture);
    glDeleteRenderbuffers(1, &this->sceneRenderBuffer);
}

#pragma region PRIVATE
void PolyEngine::Editor::Views::SceneEditorView::InitScene()
{
    glEnable(GL_DEPTH_TEST);
}

void PolyEngine::Editor::Views::SceneEditorView::RenderScene()
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->sceneFramebuffer);

    glViewport(0, 0, this->windowWidth, this->windowHeight);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PolyEngine::Editor::Views::SceneEditorView::InitSceneFramebuffer()
{
    glGenFramebuffers(1, &this->sceneFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, this->sceneFramebuffer);

    glGenTextures(1, &this->sceneTexture);
    glBindTexture(GL_TEXTURE_2D, this->sceneTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->windowWidth, this->windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->sceneTexture, 0);

    glGenRenderbuffers(1, &this->sceneRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, this->sceneRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->windowWidth, this->windowHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->sceneRenderBuffer);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER: Framebuffer is not complete!" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void PolyEngine::Editor::Views::SceneEditorView::RescaleSceneFramebuffer()
{
    glBindTexture(GL_TEXTURE_2D, this->sceneTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->windowWidth, this->windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->sceneTexture, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, this->sceneRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->windowWidth, this->windowHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->sceneRenderBuffer);
}

#pragma endregion PRIVATE
