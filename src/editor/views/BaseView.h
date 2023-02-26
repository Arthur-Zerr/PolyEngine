//
// Created by Arthur Zerr on 23.02.23.
//

#ifndef POLYEDITOR_BASEVIEW_H
#define POLYEDITOR_BASEVIEW_H

#include <string>
#include <imgui/imgui.h>

namespace PolyEngine::Editor::Views
{
    class BaseView
    {
    public:
        /**
         * Initializes the view
         */
        virtual void Init();

        /**
         * Renders the view to the Viewport
         */
        virtual void Render();

        /**
         * Disposes the view
         */
        virtual void Dispose();

    };
}

#endif //POLYEDITOR_BASEVIEW_H
