//
// Created by Arthur Zerr on 12.02.23.
//

#ifndef POLYRPG_SCENEEDITORVIEW_H
#define POLYRPG_SCENEEDITORVIEW_H

#include <imgui/imgui.h>
#include <glad/glad.h>
#include <iostream>

#include "BaseView.h"
#include "../../engine/Scene.h"

namespace PolyEngine::Editor::Views
{
    /**
     * Contains the renders scene for editing it
     */
    class SceneEditorView : BaseView
    {
    public:
        Engine::Scene currentScene;
        std::string viewName;

        SceneEditorView();

        void Init() override;

        void Render() override;

        void Dispose() override;

    private:
        int windowWidth, windowHeight;
        GLuint sceneFramebuffer;
        GLuint sceneRenderBuffer;
        GLuint sceneTexture;

        void InitScene();
        void RenderScene();

        void InitSceneFramebuffer();
        void RescaleSceneFramebuffer();
    };
}


#endif //POLYRPG_SCENEEDITORVIEW_H
