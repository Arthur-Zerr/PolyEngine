//
// Created by Arthur Zerr on 20.02.23.
//

#include "EditorView.h"

PolyEngine::Editor::EditorView::EditorView(GLFWwindow *window)
{
    this->currentScene = Engine::Scene{};
    this->currentGameObject = Engine::GameObject{};
    this->currentGameObject.name;
    strcpy(this->currentGameObject.name, "Test");

    this->window = window;
}

#pragma region PUBLIC

void PolyEngine::Editor::EditorView::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.Fonts->AddFontFromFileTTF("fonts/EditorFont.ttf", 14);

    ImFontConfig font_config;
    font_config.OversampleH = 2;
    font_config.OversampleV = 2;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    CustomImGuiStyle::setDarkStyle();




    this->sceneExplorerView.Init();
    this->sceneEditorView.Init();
//    this->gameObjectPropertiesView.Init();
    this->fileViewExplorer.Init();
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
    ImGuiViewport *viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::Begin("EditorView", nullptr, window_flags);
    ImGuiID editorViewId = ImGui::GetID("EditorView");
    ImGui::DockSpace(editorViewId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

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

#pragma endregion PUBLIC

#pragma region PRIVATE

void PolyEngine::Editor::EditorView::renderMenuBar()
{
    if (ImGui::BeginMenu("File"))
    {
        ImGui::Separator();
        if (ImGui::MenuItem("\uE70C Close", ""))
        {
            glfwSetWindowShouldClose(window, true);
        }
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
    std::cout << viewport->Size.x << std::endl;
    std::cout << viewport->Size.y << std::endl;

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

#pragma endregion PRIVATE