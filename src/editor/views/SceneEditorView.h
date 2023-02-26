//
// Created by Arthur Zerr on 12.02.23.
//

#ifndef POLYRPG_SCENEEDITORVIEW_H
#define POLYRPG_SCENEEDITORVIEW_H

#include <imgui/imgui.h>

#include "BaseView.h"

namespace PolyEngine::Editor::Views
{
    /**
     * Contains the renders scene for editing it
     */
    class SceneEditorView : BaseView
    {
    public:
        std::string viewName;

        SceneEditorView();


        void Init() override;

        void Render() override;

        void Dispose() override;
    };
}


#endif //POLYRPG_SCENEEDITORVIEW_H
