//
// Created by Arthur Zerr on 11.02.23.
//

#ifndef POLYRPG_DEBUGVIEW_H
#define POLYRPG_DEBUGVIEW_H

#include <imgui/imgui.h>

namespace Engine::Views {
    class DebugView
    {
    public:
        void Init();
        void Render();
    };
}


#endif //POLYRPG_DEBUGVIEW_H
