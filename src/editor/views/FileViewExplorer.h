//
// Created by Arthur Zerr on 23.02.23.
//

#ifndef POLYEDITOR_FILEVIEWEXPLORER_H
#define POLYEDITOR_FILEVIEWEXPLORER_H

#include <imgui/imgui.h>

#include "BaseView.h"

namespace PolyEngine::Editor::Views
{
    /**
     * File Explorer
     */
    class FileViewExplorer : BaseView
    {
    public:
        std::string viewName;

        FileViewExplorer();

        void Init() override;

        void Render() override;

        void Dispose() override;
    };
}

#endif //POLYEDITOR_FILEVIEWEXPLORER_H
