//
// Created by Arthur Zerr on 20.02.23.
//

#include "EditorView.h"

PolyEngine::Editor::EditorView::EditorView(GLFWwindow *window)
{
    this->window = window;
}

void PolyEngine::Editor::EditorView::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    CustomImGuiStyle::SetStyle();

    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
}

void PolyEngine::Editor::EditorView::Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                    ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;


    ImGuiDockNodeFlags dockspace_flags =
            ImGuiDockNodeFlags_PassthruCentralNode;

    ImGui::Begin("EditorView", nullptr, window_flags);

    ImGuiID editorViewId = ImGui::GetID("EditorView");
    ImGui::DockSpace(editorViewId, ImVec2(0.0f, 0.0f), dockspace_flags);

    if (firstRun)
    {
        std::cout << "First run" << std::endl;
        this->createDockSpace(editorViewId);
        this->firstRun = false;
    }

    if (ImGui::BeginMenuBar())
    {
        this->renderMenuBar();
        ImGui::EndMenuBar();
    }

    ImGui::End();

    this->sceneExplorerView.Render();
    this->sceneEditorView.Render();
    this->gameObjectPropertiesView.Render();
    this->fileViewExplorer.Render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void PolyEngine::Editor::EditorView::Dispose()
{
    this->sceneExplorerView.Dispose();
    this->sceneEditorView.Dispose();
    this->gameObjectPropertiesView.Dispose();
    this->fileViewExplorer.Dispose();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void PolyEngine::Editor::EditorView::renderMenuBar()
{
    if (ImGui::BeginMenu("File"))
    {
        ImGui::Separator();
        if (ImGui::MenuItem("Flag: NoSplit", ""))
        {
        }

        ImGui::Separator();
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit"))
    {
        ImGui::Separator();
        if (ImGui::MenuItem("Flag: NoSplit", ""))
        {
        }

        ImGui::Separator();
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Scene"))
    {
        ImGui::Separator();
        if (ImGui::MenuItem("Flag: NoSplit", ""))
        {
        }

        ImGui::Separator();
        ImGui::EndMenu();
    }
}

void PolyEngine::Editor::EditorView::createDockSpace(ImGuiID viewId)
{
    ImGui::DockBuilderRemoveNode(viewId);
    ImGui::DockBuilderAddNode(viewId, ImGuiDockNodeFlags_DockSpace);
    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::DockBuilderSetNodeSize(viewId, viewport->Size);

    // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
    ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(viewId, ImGuiDir_Left, 0.20f, NULL, &viewId);
    ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(viewId, ImGuiDir_Right, 0.20f, NULL, &viewId);
    ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(viewId, ImGuiDir_Down, 0.20f, NULL, &viewId);

    // Add more Views later
    ImGui::DockBuilderDockWindow(this->fileViewExplorer.viewName.c_str(), dock_id_bottom);
    ImGui::DockBuilderDockWindow(this->sceneExplorerView.viewName.c_str(), dock_id_left);
    ImGui::DockBuilderDockWindow(this->gameObjectPropertiesView.viewName.c_str(), dock_id_right);

    ImGui::DockBuilderFinish(viewId);
}

